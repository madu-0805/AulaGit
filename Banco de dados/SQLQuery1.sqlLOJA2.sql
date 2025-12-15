-- ===========================
-- 1. Criar banco de dados
-- ===========================
CREATE DATABASE Loja2;
USE Loja2;

-- ===========================
-- 2. Criar tabela Cliente
-- ===========================
CREATE TABLE Clientes(
ClienteId   INT IDENTITY(100,1),
Nome        VARCHAR(50) NOT NULL,
Email       VARCHAR(100) UNIQUE,
CONSTRAINT Pk_Cliente PRIMARY KEY (ClienteId)
--PK :PRIMARY KEY
);



-- ===========================
-- 3. Criar tabela Pedido
-- ===========================
CREATE TABLE Pedido(
PedidoId INT IDENTITY(100,1),
DataPedido DATE NOT NULL,
Valor DECIMAL(10,2),
ClienteId INT ,
CONSTRAINT Pk_Pedido PRIMARY KEY(PedidoId),
CONSTRAINT Fk_Pedido_Cliente FOREIGN KEY(ClienteId) REFERENCES Clientes(ClienteId)-- ON DELETE CASCADE 
---FK : FOREIGN KEY(CHAVE ESTRANGEIRA)
);


-- ===========================
-- 4. Inserir dados iniciais
-- ===========================
INSERT INTO Clientes VALUES -- NOME,EMAIL
('Ravi','Ravi@augusto.com'),
('Matteo','Matteo@carvalho.com'),
('Antonella' ,NULL);

INSERT INTO Pedido VALUES 
('2025-09-11','199.90',100),
('2025-09-10','49.90',100),
('2025-09-09','350.00',101);


-- ===========================
-- 5. Consultas de teste
-- ===========================
SELECT * FROM Clientes;
SELECT * FROM Pedido;
SELECT * FROM Clientes;

- ===========================
-- 6. Atualizar dados
-- ===========================
-- Alterar nome
--UPDATE 
UPDATE Clientes SET Nome ='Mary'--ALTERE
WHERE ClienteId = 101
SELECT * FROM Clientes;


--AJUSTAR UM VALOR DE UM PEDIDO
SELECT * FROM Pedido;
UPDATE Pedido SET Valor =Valor + '10.00'
WHERE PedidoId = 101
SELECT * FROM Pedido;

-- MUDAR STORAGE PROCEDURE // PROCEDIMENTO ARMAZENADO 
-- RENAME -RENOMEAR

EXEC sp_rename 'Clientes','Cliente'
SELECT * FROM Cliente;

--- RENOMEAR A COLUNA VALOR -> VALORTOTAL
EXEC sp_rename'Pedido.Valor', 'ValorTotal','COLUMN'

SELECT*FROM Pedido;

-- ALTERAR O TIPO DO DADO
ALTER TABLE Cliente
ALTER COLUMN Nome VARCHAR(120) NOT NULL


-- Ver a estrutura da tabela
EXEC sp_help'Cliente'

-- ===========================
-- 7. Excluir cliente e testar ON DELETE CASCADE
-- ===========================

DELETE Cliente 
WHERE ClienteId = 100

--ALTERAR TABELA PEDIDO PARA INSERIR 
-- ON DELETE CASCADE 
ALTER TABLE Pedido
DROP CONSTRAINT FK_Pedido_Cliente


-- APAGANDO CHAVE PRIMARIA DA TABELA Pedido
ALTER TABLE Pedido
DROP CONSTRAINT PK_Pedido


--RECRIAR A CHAVE PRIMARIA 
ALTER TABLE Pedido
ADD CONSTRAINT PK_Pedido PRIMARY KEY(PedidoId)
SELECT*FROM Pedido;

 --RECRIAR FK COM ON DELETE CASCADE
 ALTER TABLE Pedido
 ADD CONSTRAINT FK_Pedido_Cliente
 FOREIGN KEY(ClienteId) REFERENCES Cliente(ClienteId)
 ON DELETE CASCADE 

 SELECT *FROM Cliente;
 SELECT* FROM Pedido;

 DELETE Cliente
 WHERE ClienteId = 100

 SELECT *FROM Cliente;
 SELECT* FROM Pedido;
 --- adicionar novas colunas
ALTER TABLE Cliente
ADD CPF VARCHAR(11)
SELECT * FROM Cliente;


---ATIVIDADE
-- 1 CPF
UPDATE Cliente SET CPF = '98765432100'
WHERE ClienteId = 101;
UPDATE Cliente SET CPF = '45612378999'
WHERE ClienteId = 102;
SELECT * FROM Cliente;

-- 2 CEP
ALTER TABLE Cliente  ADD CEP VARCHAR(15);
ALTER TABLE Cliente ADD CONSTRAINT UQ_Cliente_CEP UNIQUE (CEP);
UPDATE Cliente SET CEP ='000000001'
WHERE ClienteId = 101;
UPDATE Cliente SET CEP ='000000002'
WHERE ClienteId = 102;
SELECT * FROM Cliente;



 --3 RG
ALTER TABLE Cliente
 ADD RG VARCHAR(11)
CREATE UNIQUE INDEX UQ_Cliente_RG
ON Cliente (RG)
WHERE RG IS NOT NULL;
UPDATE Cliente SET RG ='123456789' 
WHERE ClienteId = 101;
UPDATE Cliente SET RG ='987654321'
WHERE ClienteId = 102;