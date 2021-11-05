
-- PL PARA DAR DE ALTA AREA REQUIRIENTE, NO DEVUELVE NADA.
-- SI YA EXISTE EL AREA NO INSERTA Y MUESTRA MENSAJE, DE LO CONTRARIO, INSERTA Y MUESTRA MENSAJE.
DROP FUNCTION Requiriente(opcion INTEGER, nombre VARCHAR, descrip VARCHAR);
CREATE OR REPLACE FUNCTION Requiriente(opcion INTEGER, nombre VARCHAR, descrip VARCHAR) RETURNS VOID AS $BODY$
DECLARE
    Consulta INTEGER := (SELECT id_area_requiriente FROM area_requiriente WHERE UPPER(nombre_area) = UPPER(nombre));
BEGIN
    CASE (opcion)
    --- Si se recibe el número 1 como parámetro, se da de Alta ---
        WHEN (1) THEN
            IF Consulta > 0 THEN
                RAISE NOTICE 'YA EXISTE ESE AREA';
            ELSE
                INSERT INTO area_requiriente (nombre_area,descripcion,estatus) VALUES (nombre,descrip,1);
                RAISE NOTICE 'DADO DE ALTA';
            END IF;
     --- Si se recibe el número 2 como parámetro, se da de Baja ---
        WHEN (2) THEN
            IF Consulta > 0 THEN
                UPDATE area_requiriente SET estatus = 0 WHERE UPPER(nombre_area) = UPPER(nombre);
                RAISE NOTICE 'DADO DE BAJA';
            ELSE
                RAISE NOTICE 'NO EXISTE EL AREA';
            END IF;
        ELSE
            RAISE NOTICE 'OPCION NO VALIDA';
    END CASE;
EXCEPTION
    WHEN SQLSTATE 'YE001' THEN
        RAISE NOTICE 'memoria virtual está agotada';
    WHEN SQLSTATE 'YE002' THEN
        RAISE NOTICE 'el preprocesador ha generado algo que la biblioteca no conoce';
    WHEN SQLSTATE '22002' THEN
        RAISE NOTICE 'Se devolvió un valor nulo';
    ROLLBACK;
    COMMIT;
END;
$BODY$ LANGUAGE 'plpgsql';
