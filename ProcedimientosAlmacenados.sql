
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
