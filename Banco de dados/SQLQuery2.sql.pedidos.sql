---Sistema de Pedidos Simples
CREATE TABLE Pedidos (
    IdPedido INT PRIMARY KEY,
    Cliente VARCHAR(100),
    Produto VARCHAR(100),
    Quantidade INT
);


INSERT INTO Pedidos( IdPedido,  Cliente, Produto, Quantidade) VALUES
(1, 'Maria Silva', 'Pizza', 2),
(2, 'João Santos', 'Hambúrguer', 3),
(3, 'Ana Oliveira', 'Pizza', 1),
(4, 'Carlos Pereira', 'Refrigerante', 4),
(5, 'Fernanda Souza', 'Lasanha', 2),
(6, 'Lucas Andrade', 'Pizza', 5);


SELECT * FROM Pedidos
WHERE Cliente = 'Maria Silva'; 

SELECT * FROM Pedidos
WHERE Produto = 'Pizza';

SELECT Cliente, Quantidade FROM Pedidos;