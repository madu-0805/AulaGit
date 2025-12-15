CREATE DATABASE VendasOnline
GO

USE  VendasOnline;

GO
CREATE TABLE Categoria(
	CategoriaId INT PRIMARY KEY IDENTITY NOT NULL,
	Nome VARCHAR(100)
)

CREATE TABLE StatusPedido(
	StatusId INT PRIMARY KEY IDENTITY  NOT NULL,
	Nome VARCHAR(50) NULL
)

CREATE TABLE Cliente (
    ClienteID INT IDENTITY PRIMARY KEY,
    Nome VARCHAR(50) NOT NULL,
    Sobrenome VARCHAR(50) NOT NULL,
    Email VARCHAR(100) NOT NULL,
    Telefone VARCHAR(20),
    DataCadastro DATE NOT NULL
);
GO

CREATE TABLE Produto (
    ProdutoID INT IDENTITY PRIMARY KEY,
    NomeProduto VARCHAR(100) NOT NULL,
    CategoriaID INT NOT NULL FOREIGN KEY REFERENCES Categoria(CategoriaId),
    Preco DECIMAL(10, 2) NOT NULL,
    QuantidadeEstoque INT NOT NULL
);
GO
CREATE TABLE Pedido(
    PedidoID INT IDENTITY PRIMARY KEY,
    ClienteID INT NOT NULL FOREIGN KEY REFERENCES Cliente(ClienteID),
    DataPedido DATE NOT NULL,
    ValorTotal DECIMAL(10, 2) NOT NULL,
    StatusID INT NOT NULL FOREIGN KEY REFERENCES StatusPedido(StatusId)
);
GO
CREATE TABLE DetalhesPedido (
    DetalhePedidoID INT IDENTITY PRIMARY KEY,
    PedidoID INT NOT NULL FOREIGN KEY REFERENCES Pedido(PedidoID),
    ProdutoID INT NOT NULL FOREIGN KEY REFERENCES Produto(ProdutoID),
    Quantidade INT NOT NULL,
    PrecoUnitario DECIMAL(10, 2) NOT NULL
);
GO
CREATE TABLE Fornecedor (
    FornecedorID INT IDENTITY PRIMARY KEY,
    NomeFornecedor VARCHAR(100) NOT NULL,
    NomeContato VARCHAR(50),
    EmailContato VARCHAR(100),
    Telefone VARCHAR(20)
);
GO
CREATE TABLE ProdutoFornecedor (
    ProdutoFornecedorID INT IDENTITY PRIMARY KEY,
    ProdutoID INT NOT NULL FOREIGN KEY REFERENCES Produto(ProdutoID),
    FornecedorID INT NOT NULL FOREIGN KEY REFERENCES Fornecedor(FornecedorID),
    PrecoFornecimento DECIMAL(10, 2) NOT NULL
);
GO



-- Inserindo dados na tabela StatusPedido
INSERT INTO  StatusPedido(Nome) values
('Enviado'),
('Pendente'),
('Cancelado');
GO

-- Inserindo dados na tabela Categoria
INSERT INTO  Categoria(Nome) values
('Periféricos'),
('Eletrônicos'),
('Móveis'),
('Eletrodomésticos');
GO

-- Inserindo dados na tabela Cliente
INSERT INTO Cliente (Nome, Sobrenome, Email, Telefone, DataCadastro) VALUES
('João', 'Silva', 'joao.silva@email.com', '11999998888', '2022-01-15'),
('Maria', 'Oliveira', 'maria.oliveira@email.com', '21988887777', '2023-03-10'),
('Carlos', 'Souza', 'carlos.souza@email.com', '31977776666', '2021-08-23'),
('Ana', 'Santos', 'ana.santos@email.com', '41966665555', '2020-05-12'),
('Beatriz', 'Lima', 'beatriz.lima@email.com', '51955554444', '2019-12-30'),
('Fernando', 'Almeida', 'fernando.almeida@email.com', '31912345678', '2023-02-10'),
('Juliana', 'Ferreira', 'juliana.ferreira@email.com', '21987654321', '2022-11-20'),
('Lucas', 'Pereira', 'lucas.pereira@email.com', '41945678901', '2021-09-15'),
('Carla', 'Mendes', 'carla.mendes@email.com', '11965498732', '2020-06-25'),
('Thiago', 'Gomes', 'thiago.gomes@email.com', '51978965412', '2023-01-05'),
('Priscila', 'Barbosa', 'priscila.barbosa@email.com', '21965412387', '2021-03-30'),
('Rodrigo', 'Neves', 'rodrigo.neves@email.com', '31978541236', '2022-12-18'),
('Marcela', 'Costa', 'marcela.costa@email.com', '41985236974', '2020-02-27'),
('André', 'Silveira', 'andre.silveira@email.com', '51996325841', '2023-08-01'),
('Gabriela', 'Nunes', 'gabriela.nunes@email.com', '11998765432', '2019-05-14');
GO

-- Inserindo dados na tabela Fornecedore
INSERT INTO Fornecedor (NomeFornecedor, NomeContato, EmailContato, Telefone) VALUES
('Dell Brasil', 'Carlos Andrade', 'carlos.andrade@dell.com', '1134567890'),
('Wacom', 'Laura Ribeiro', 'laura.ribeiro@wacom.com', '2145678901'),
('Apple Store', 'Pedro Neves', 'pedro.neves@apple.com', '3145678902'),
('Samsung Distribuidora', 'Rafael Almeida', 'rafael.almeida@samsung.com', '4145678903'),
('HP do Brasil', 'Fernanda Costa', 'fernanda.costa@hp.com', '5145678904'),
('Lenovo Brasil', 'Rafael Torres', 'rafael.torres@lenovo.com', '1134567811'),
('LG Electronics', 'Camila Souza', 'camila.souza@lg.com', '2145678911'),
('JBL Distribuidora', 'Lucas Andrade', 'lucas.andrade@jbl.com', '3145678922'),
('Logitech Brasil', 'Roberta Cunha', 'roberta.cunha@logitech.com', '4145678933'),
('DXRacer', 'Marcos Lima', 'marcos.lima@dxracer.com', '5145678944'),
('Brastemp', 'Paula Martins', 'paula.martins@brastemp.com', '1145678955'),
('Nespresso', 'Renato Alves', 'renato.alves@nespresso.com', '2245678966'),
('Xiaomi Distribuidora', 'Vanessa Ribeiro', 'vanessa.ribeiro@xiaomi.com', '3345678977'),
('Samsung Brasil', 'Leonardo Rocha', 'leonardo.rocha@samsung.com', '4445678988'),
('HyperX', 'Larissa Monteiro', 'larissa.monteiro@hyperx.com', '5545678999');
GO

-- Inserindo dados na tabela Produto
INSERT INTO Produto (NomeProduto, CategoriaID, Preco, QuantidadeEstoque) VALUES
('Computador Dell Inspiron', 2, 4500.00, 25),
('Mesa Digitalizadora Wacom Intuos', 1, 1200.00, 40),
('iPhone 14', 2, 8000.00, 15),
('Smart TV Samsung 55"', 2, 3500.00, 10),
('Impressora HP DeskJet', 1, 650.00, 30),
('Notebook Lenovo Ideapad 3', 2, 3000.00, 50),
('Monitor LG UltraWide 29"', 2, 1500.00, 35),
('Fone de Ouvido JBL', 1, 300.00, 100),
('Cadeira Gamer DXRacer', 3, 1100.00, 20),
('Mouse Gamer Logitech G203', 1, 200.00, 150),
('Geladeira Brastemp Frost Free', 4, 4500.00, 10),
('Cafeteira Nespresso', 4, 800.00, 25),
('Smartphone Xiaomi Redmi Note 12', 2, 2500.00, 40),
('Tablet Samsung Galaxy Tab A7', 2, 1200.00, 30),
('Headset HyperX Cloud Stinger', 1, 350.00, 60);
GO

-- Inserindo dados na tabela ProdutoFornecedor
INSERT INTO ProdutoFornecedor (ProdutoID, FornecedorID, PrecoFornecimento) VALUES
(1, 1, 4000.00), -- Computador Dell fornecido pela Dell Brasil
(2, 2, 1000.00), -- Mesa Digitalizadora fornecida pela Wacom
(3, 3, 7000.00), -- iPhone fornecido pela Apple Store
(4, 4, 3000.00), -- Smart TV fornecida pela Samsung
(5, 5, 550.00),  -- Impressora fornecida pela HP
(6, 6, 4000.00), -- Geladeira fornecida pela Brastemp
(7, 7, 700.00), -- Cafeteira fornecida pela Nespresso
(8, 8, 2200.00), -- Smartphone Xiaomi fornecido pela Xiaomi
(9, 9, 1000.00), -- Tablet Samsung fornecido pela Samsung
(10, 10, 300.00), -- Headset HyperX fornecido pela HyperX
(11, 5, 950.00), -- Mouse Gamer fornecido pela Logitech
(12, 3, 250.00), -- Fone de Ouvido fornecido pela JBL
(13, 2, 1400.00), -- Monitor fornecido pela LG
(14, 1, 2700.00), -- Notebook fornecido pela Lenovo
(15, 4, 900.00); -- Cadeira Gamer fornecida pela DXRacer
GO

-- Inserindo dados na tabela Pedido
INSERT INTO Pedido (ClienteID, DataPedido, ValorTotal, StatusID) VALUES
(1, '2024-10-01', 5700.00, 2),
(2, '2024-11-15', 1200.00, 3),
(3, '2024-11-25', 4500.00, 1),
(4, '2024-11-28', 3500.00, 2),
(5, '2024-11-29', 650.00, 3),
(6, '2024-10-10', 350.00, 2),
(7, '2024-11-01', 2500.00, 1),
(8, '2024-11-15', 800.00, 3),
(9, '2024-11-20', 1200.00, 2),
(10, '2024-11-29', 4000.00, 3);
GO

-- Inserindo dados na tabela DetalhesPedido
INSERT INTO DetalhesPedido (PedidoID, ProdutoID, Quantidade, PrecoUnitario) VALUES
(1, 1, 1, 4500.00), -- Computador Dell no Pedido de Joao
(1, 2, 1, 1200.00), -- Mesa Digitalizadora no Pedido de Joao
(2, 2, 1, 1200.00), -- Mesa Digitalizadora no Pedido de Maria
(3, 1, 1, 4500.00), -- Computador Dell no Pedido de Carlos
(4, 4, 1, 3500.00), -- Smart TV Samsung no Pedido de Ana
(5, 5, 1, 650.00),  -- Impressora HP no Pedido de Beatriz
(6, 10, 1, 350.00), -- Headset HyperX no Pedido de Priscila
(7, 8, 1, 2500.00), -- Smartphone Xiaomi no Pedido de Rodrigo
(8, 7, 1, 800.00), -- Cafeteira no Pedido de Marcela
(9, 9, 1, 1200.00), -- Tablet no Pedido de Andre
(10, 6, 1, 4000.00); -- Geladeira no Pedido de Gabriela



-- 1. Nome completo
SELECT Nome + '  '  + Sobrenome AS NomeCompleto
FROM Cliente;

-- 2. Nome do produto em maiúsculas
SELECT NomeProduto, UPPER(NomeProduto) AS NomeMaiusculo
FROM Produto;

-- 3. Três primeiros caracteres do nome
SELECT Nome, LEFT(Nome, 3) AS PrimeirasLetras
FROM Cliente;

-- 4. Posição do @ no e-mail
SELECT Email, CHARINDEX('@', Email) AS PosicaoArroba
FROM Cliente;

-- 5. Desconto de 15%
SELECT NomeProduto, Preco, Preco * 0.85 AS PrecoComDesconto
FROM Produto;


-- 6. Preço arredondado (2 casas) Retorna a soma de uma coluna numérica.			
SELECT NomeProduto, ROUND(Preco, 2) AS PrecoArredondado
FROM Produto;

-- 7. Valor absoluto do estoque (Retorna o valor absoluto de um número.)
SELECT NomeProduto, ABS(QuantidadeEstoque) AS EstoqueAbsoluto
FROM Produto;

-- 8. Preço ao quadrado(Retorna o valor de um número elevado a uma potência.				)
SELECT NomeProduto, POWER(Preco, 2) AS PrecoAoQuadrado
FROM Produto;

-- 9. Ano e mês do pedido
SELECT PedidoID, YEAR(DataPedido) AS Ano, MONTH(DataPedido) AS Mes
FROM Pedido;

-- 10. Anos de cadastro do cliente
SELECT Nome, Sobrenome,
       DATEDIFF(YEAR, DataCadastro, GETDATE()) AS AnosDeCadastro
FROM Cliente;

-- 11. Data de entrega prevista (+30 dias)
SELECT PedidoID, DataPedido, DATEADD(DAY, 30, DataPedido) AS DataEntregaPrevista
FROM Pedido;

-- 12. Dia da semana do pedido
SELECT PedidoID, DATENAME(WEEKDAY, DataPedido) AS DiaSemana
FROM Pedido;

-- 13. Total de produtos no estoque (SUM()	Retorna a soma de uma coluna numérica.)
SELECT SUM(QuantidadeEstoque) AS TotalEstoque
FROM Produto;

-- 14. Preço médio dos produtos (AVG()	Retorna a média dos valores de uma coluna numérica.	)
SELECT AVG(Preco) AS PrecoMedio
FROM Produto;

-- 15. Maior e menor preço
SELECT MAX(Preco) AS PrecoMaximo,
       MIN(Preco) AS PrecoMinimo
FROM Produto;

-- 16. Total de pedidos
SELECT COUNT(*) AS TotalPedidos
FROM Pedido;


-- 17. Total de pedidos por cliente
SELECT c.Nome + ' ' + c.Sobrenome AS Cliente,
       COUNT(p.PedidoID) AS TotalPedidos
FROM Pedido p
JOIN Cliente c ON p.ClienteID = c.ClienteID
GROUP BY c.Nome, c.Sobrenome;



-- 18. Total de estoque por categoria
SELECT cat.Nome AS Categoria,
       SUM(p.QuantidadeEstoque) AS TotalEstoque
FROM Produto p
JOIN Categoria cat ON p.CategoriaID = cat.CategoriaId
GROUP BY cat.Nome;



-- 19. Número de produtos por categoria
SELECT cat.Nome AS Categoria,
       COUNT(p.ProdutoID) AS QtdProdutos
FROM Produto p
JOIN Categoria cat ON p.CategoriaID = cat.CategoriaId
GROUP BY cat.Nome;



-- 20. Soma dos valores totais dos pedidos agrupados
SELECT c.Nome + ' ' + c.Sobrenome AS Cliente,
       SUM(p.ValorTotal) AS SomaPedidos
FROM Pedido p
JOIN Cliente c ON p.ClienteID = c.ClienteID
GROUP BY c.Nome, c.Sobrenome;