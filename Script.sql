--SCRIPT DE BD PROYECTO HOSPITAL

CREATE DATABASE ProyectoHospital;

--Area Requiriente
CREATE TABLE area_requiriente(
	id_area_requiriente SERIAL NOT NULL,
	PRIMARY KEY(id_area_requiriente),
	nombre_area VARCHAR,
	descripcion VARCHAR,
	estatus INTEGER
);

--Insumos
CREATE TABLE insumos(
	id_insumos SERIAL NOT NULL,
	PRIMARY KEY(id_insumos),
	id_area_requiriente INTEGER REFERENCES area_requiriente,
	nombre_producto VARCHAR,
	stock INTEGER,
	estatus INTEGER
);

--Pedidos
CREATE TABLE pedidos(
	id_pedidos SERIAL NOT NULL,
	PRIMARY KEY(id_pedidos),
	id_area_requiriente INTEGER REFERENCES area_requiriente,
	descripcion VARCHAR,
	fecha_creacion DATE,
	hora_creacion TIME	
);

--Detalle_Pedidos
CREATE TABLE detalle_pedidos(
	id_detalle_pedidos SERIAL NOT NULL,
	PRIMARY KEY(id_detalle_pedidos),
	id_pedidos INTEGER REFERENCES pedidos,
	id_insumos INTEGER REFERENCES insumos,
	piezas INTEGER
);

--Pedidos Despachados
CREATE TABLE pedidos_despachados(
	id_pedidos_despachados SERIAL NOT NULL,
	PRIMARY KEY(id_pedidos_despachados),
	id_pedidos INTEGER REFERENCES pedidos,
	estatus INTEGER,
	fecha_recibido DATE,
	hora_recibido TIME
);

--Almacen
CREATE TABLE almacen(
	id_almacen SERIAL NOT NULL,
	PRIMARY KEY(id_almacen),
	id_pedidos_despachados INTEGER REFERENCES pedidos_despachados,
	total REAL
);

--Detalle Almacen
CREATE TABLE detalle_almacen(
	id_detalle_almacen SERIAL NOT NULL,
	PRIMARY KEY(id_detalle_almacen),
	id_almacen INTEGER REFERENCES almacen,
	id_insumos INTEGER REFERENCES insumos,
	piezas INTEGER,
	precio REAL,
	subtotal REAL
);