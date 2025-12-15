/*criando Base de dados
CREATE	DATABASE Empresa;
/*acessando banco criado*/
USE Empresa;

--Criar tabela / entidade de funcionarios
CREATE TABLE Funcionario (
Codigo INT PRIMARY KEY,
Nome VARCHAR(100)
);
-- Inserir dados na tabela
INSERT INTO Funcionario(Codigo, Nome) VALUES
(1,'Luis Miguel'),
(2, 'Gui Silva'),
(3, 'Maria Santos'),
(4,'Gustavo Carvalho');

--  Buscando informacao na tabela
SELECT * FROM Funcionario;


SELECT Nome FROM Funcionario;

SELECT * FROM Funcionario
WHERE Codigo > 3;

--Buscar funcionarios que o nome comeca com a letra A

SELECT * FROM Funcionario
WHERE Nome LIKE'M%';

-- ORDEM ALFABETICA 
SELECT * FROM Funcionario
ORDER BY Nome;

-- ORDEM DECRESECENTE
SELECT * FROM Funcionario
ORDER BY Codigo DESC;
--DESC- DECRESENTE
--ASC- CRESCENTE

-- ATUALICAO DE REGISTROS
UPDATE Funcionario SET Nome ='Deigo '
WHERE Nome = 'Gui silva';

-- Confirmar Alteracao
SELECT  * FROM Funcionario
WHERE Nome LIKE 'Gustavo Carvalho';
 */
 -- EXCLUSAO DE DADOS 
 DELETE FROM Funcionario
 WHERE Nome = 'Gui Silva'

 SELECT * FROM Funcionario