CREATE DATABASE Loja; -- exemplos
 
 USE Loja;


CREATE TABLE Loja(
Produto INT PRIMARY KEY,
Nome VARCHAR(50),
Categoria VARCHAR(30),
Preco DECIMAL(10,2),
Estoque INT
);


CREATE TABLE Cliente(
Cliente INT PRIMARY KEY,
Nome VARCHAR(40),
Email VARCHAR(50),
Telefone VARCHAR(20)
);

CREATE TABLE Pedido(
Pedido INT PRIMARY KEY,
DataPedido DATE,
Cliente  INT FOREIGN KEY REFERENCES Cliente(Cliente)
);

CREATE TABLE ItemPedido(
Item INT PRIMARY KEY,
Pedido INT FOREIGN KEY REFERENCES Pedido(Pedido),-- (pedido) chave estrangeira
Produto INT FOREIGN KEY REFERENCES Loja(Produto),-- (produto) chave estrangeira
Quantidade INT
);

