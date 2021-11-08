
-- PL PARA DAR DE ALTA AREA REQUIRIENTE, NO DEVUELVE NADA.
-- SI YA EXISTE EL AREA NO INSERTA Y MUESTRA MENSAJE, DE LO CONTRARIO, INSERTA Y MUESTRA MENSAJE.
DROP FUNCTION Requiriente(opcion INTEGER, nombre VARCHAR, descrip VARCHAR);
CREATE OR REPLACE FUNCTION Requiriente(opcion INTEGER, nombre VARCHAR, descrip VARCHAR) RETURNS VARCHAR AS $BODY$
DECLARE
    Consulta INTEGER := (SELECT id_area_requiriente FROM area_requiriente WHERE UPPER(nombre_area) = UPPER(nombre));
    Baja_repetida INTEGER;
BEGIN
    CASE (opcion)
    --- Si se recibe el número 1 como parámetro, se da de Alta ---
        WHEN (1) THEN
            IF Consulta > 0 THEN
                RETURN 'YA EXISTE ESE AREA';
            ELSE
                INSERT INTO area_requiriente (nombre_area,descripcion,estatus) VALUES (nombre,descrip,1);
                RETURN 'DADO DE ALTA';
            END IF;
     --- Si se recibe el número 2 como parámetro, se da de Baja ---
        WHEN (2) THEN
            IF Consulta > 0 THEN
                Baja_repetida := (SELECT estatus FROM area_requiriente WHERE UPPER(nombre_area) = UPPER(nombre));
                IF Baja_repetida = 0 THEN
                    RETURN 'YA HA SIDO DE BAJA CON ANTERIORIDAD';
                ELSE
                    UPDATE area_requiriente SET estatus = 0 WHERE UPPER(nombre_area) = UPPER(nombre);
                    RETURN 'DADO DE BAJA';
                END IF;
            ELSE
                RETURN 'NO EXISTE EL AREA';
            END IF;
        ELSE
            RETURN 'OPCION NO VALIDA';
    END CASE;
EXCEPTION
    WHEN SQLSTATE 'YE001' THEN
        RETURN 'memoria virtual está agotada';
    WHEN SQLSTATE 'YE002' THEN
        RETURN 'el preprocesador ha generado algo que la biblioteca no conoce';
    WHEN SQLSTATE '22002' THEN
        RETURN 'Se devolvió un valor nulo';
    ROLLBACK;
    COMMIT;
END;
$BODY$ LANGUAGE 'plpgsql';


--DETALLE PEDIDO
-- PASAR ID_PEDIDOS DESPACHADOS, CADENA PARA INSERTAR EN ALMACEN Y CADENA DE UPDATES EN STOCK

-- CREANDO EL PL DE INSERCION.
DROP FUNCTION Insertar_Detalle(id INTEGER, cadena_restante VARCHAR);
CREATE OR REPLACE FUNCTION Insertar_Detalle(id INTEGER, cadena_restante VARCHAR) RETURNS VARCHAR AS $BODY$
DECLARE
    fecha_insercion DATE := (SELECT CURRENT_DATE);
    hora_insercion TIME := (SELECT CURRENT_TIME);
BEGIN
    -- INSERTAMOS EN DETALLE PEDIDO
    EXECUTE 'INSERT INTO detalle_pedidos(id_pedidos, id_insumos,piezas) VALUES ' || cadena_restante;

    -- INSERTAMOS EN PEDIDOS DESPACHADOS
    INSERT INTO pedidos_despachados(id_pedidos,estatus,fecha_recibido,hora_recibido) VALUES (id,'pendiente',fecha_insercion,hora_insercion);
    RETURN 'PEDIDO DADO DE ALTA CORRECTAMENTE';
EXCEPTION
    WHEN SQLSTATE '23503' THEN
        DELETE FROM pedidos WHERE id_pedidos = id;
        RETURN 'ERROR, ALGO NO COINCIDE';
    WHEN SQLSTATE '42830' THEN
        DELETE FROM pedidos WHERE id_pedidos = id;
        RETURN 'ERROR, ALGO NO COINCIDE';
    ROLLBACK;
    COMMIT;
END;
$BODY$ LANGUAGE 'plpgsql';


-- ALMACEN
-- CREANDO EL PL DE INSERCION.
DROP FUNCTION Insertar_Almacen(id INTEGER, cadena_insertar VARCHAR, cadena_restar VARCHAR);
CREATE OR REPLACE FUNCTION Insertar_Almacen(id INTEGER, cadena_insertar VARCHAR, cadena_restar VARCHAR) RETURNS VARCHAR AS $BODY$
DECLARE
    fecha_insercion DATE := (SELECT CURRENT_DATE);
    hora_insercion TIME := (SELECT CURRENT_TIME);
    verificar_actualizacion INTEGER;
    verificar_resta INTEGER;
    variable VARCHAR;
BEGIN
    
    -- CAMBIAMOS ESTATUS EN PEDIDOS DESPACHADOS
    UPDATE pedidos_despachados SET estatus = 'realizado', fecha_recibido = fecha_insercion, hora_recibido = hora_insercion WHERE id_pedidos_despachados = id;

    --SI OBTENGO 0, ERROR, SI OBTENGO 1 SIGUE
    verificar_actualizacion := (SELECT COUNT(*) FROM pedidos_despachados WHERE id_pedidos_despachados=id AND estatus = 'realizado');

    -- SI ES CERO, LO QUIEBRO Y ASIGNO VALOR
    IF verificar_actualizacion = 0 THEN
        variable := 'ERROR EN ACTUALIZAR';
        EXECUTE 'INSERT INTO almacen(id_pedidos_despachados, id_insumos,piezas) VALUES (0,0,3)';
    END IF;

    -- SI POR ERROR SE ASIGNA UN INSUMO NO EXISTENTE, SE VA A QUEBRAR
    -- INSERTAMOS EN DETALLE ALMACEN
    EXECUTE 'INSERT INTO almacen(id_pedidos_despachados, id_insumos,piezas) VALUES ' || cadena_insertar;

    -- SI TODO ESTA CORRECTO RESTAMOS
    --DESCONTAMOS DE INSUMOS
    EXECUTE cadena_restar;

    -- SI EXISTE ALGUN NUMERO NEGATIVO HUBO UN ERROR Y QUEBRAMOS
    verificar_resta := (SELECT COUNT(*) FROM insumos WHERE stock < 0);
    IF verificar_resta > 0 THEN
        variable := 'EL STOCK PEDIDO, SOBREPASA AL EXISTENTE';
        EXECUTE 'INSERT INTO almacen(id_pedidos_despachados, id_insumos,piezas) VALUES (0,0,3)';
    ELSE
        variable := 'PEDIDO RECIBIDO CORRECTAMENTE';
    END IF;

    RETURN variable;
EXCEPTION
    WHEN SQLSTATE '23503' THEN
        IF variable = 'EL STOCK PEDIDO, SOBREPASA AL EXISTENTE' THEN
            RETURN 'EL STOCK PEDIDO, SOBREPASA AL EXISTENTE';
        ELSE 
            IF variable = 'ERROR EN ACTUALIZAR' THEN
                RETURN 'ERROR EN ACTUALIZAR EL ESTATUS PEDIDO';
            ELSE
                RETURN 'ERROR, ALGO NO COINCIDE';
            END IF;
        END IF;
    WHEN SQLSTATE '42830' THEN
        IF variable = 'EL STOCK PEDIDO, SOBREPASA AL EXISTENTE' THEN
            RETURN 'EL STOCK PEDIDO, SOBREPASA AL EXISTENTE';
        ELSE 
            IF variable = 'ERROR EN ACTUALIZAR' THEN
                RETURN 'ERROR EN ACTUALIZAR EL ESTATUS PEDIDO';
            ELSE
                RETURN 'ERROR, ALGO NO COINCIDE';
            END IF;
        END IF;

    ROLLBACK;
    COMMIT;
END;
$BODY$ LANGUAGE 'plpgsql';