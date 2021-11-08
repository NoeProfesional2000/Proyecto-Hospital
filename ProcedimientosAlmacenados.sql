
-- PL PARA DAR DE ALTA AREA REQUIRIENTE, NO DEVUELVE NADA.
-- SI YA EXISTE EL AREA NO INSERTA Y MUESTRA MENSAJE, DE LO CONTRARIO, INSERTA Y MUESTRA MENSAJE.
DROP FUNCTION Requiriente(opcion INTEGER, nombre VARCHAR, descrip VARCHAR);
CREATE OR REPLACE FUNCTION Requiriente(opcion INTEGER, nombre VARCHAR, descrip VARCHAR) RETURNS VARCHAR AS $BODY$
DECLARE
    Consulta INTEGER := (SELECT id_area_requiriente FROM area_requiriente WHERE UPPER(nombre_area) = UPPER(nombre));
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
                UPDATE area_requiriente SET estatus = 0 WHERE UPPER(nombre_area) = UPPER(nombre);
                RETURN 'DADO DE BAJA';
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