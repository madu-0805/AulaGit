CREATE DATABASE Biblioteca2;

USE Biblioteca2;

CREATE TABLE Autor(
id_Autor INT PRIMARY KEY,
Nome VARCHAR(100)
);

CREATE TABLE Livro(
id_Livro INT PRIMARY KEY,
titulo VARCHAR(150),
ano INT,
id_Autor INT,
CONSTRAINT fk_livro_autor FOREIGN KEY (id_Autor)REFERENCES Autor (id_Autor)
);

CREATE TABLE Leitor(
id_Leitor INT PRIMARY KEY,
Nome VARCHAR(100),
email VARCHAR(120) UNIQUE
);
CREATE TABLE Emprestimo(
id_Emprestimo INT PRIMARY KEY, 
id_Livro INT, 
id_Leitor INT,
data_emprestimo DATE,
data_devolucao DATE
CONSTRAINT fk_empr_livro FOREIGN KEY (id_Livro) REFERENCES Livro(id_Livro),
CONSTRAINT fk_empr_leitor FOREIGN KEY(id_Leitor) REFERENCES Leitor(id_leitor),
);

INSERT INTO Autor VALUES
(1,'Jenna Evans'),
(2,'Maurice Leblanc'),
(3,'Markus Zusak'),
(4,'John Boyne');

INSERT INTO Livro VALUES
(1,'AMOR & GELATO', 2016,1),
(2,'Ladrão de Casaca', 1907,2),
(3,'A Menina que Roubava Livros',2005,3),
(4,'O Menino do Pijama Listrado',2008,4);


INSERT INTO Leitor VALUES
(1,'Maria Eduarda','maria@gmail.com'),
(2,'Gustavo','gustavo@gmail.com'),
(3,'Luis','luis@gmail.com'),
(4,'Anna','anna@gmail.com');

INSERT INTO Emprestimo VALUES
(1,1,1, '2025-09-02','2025-09-09'),
(2,2,3,'2025-08-27','2025-09-05'),
(3,3,4,'2025-05-01','2025-06-10'),
(4,4,2,'2025-05-10', '2025-04-19');


--FUNCOES

-- COUNT : conta o total de registros
SELECT COUNT (*) AS QtdLeitores
FROM Leitor;

SELECT * FROM Leitor;


-- COUNT + GROUP BY: Emprestimos por leitor
SELECT l.nome AS Leitor,
COUNT(e.id_Emprestimo) AS QtdEmprestimo
FROM Emprestimo e
JOIN Leitor l ON l.id_Leitor = e.id_Leitor
GROUP BY l.nome
ORDER BY QtdEmprestimo DESC


-- MIN /MAX SOBRE ANO DE PUBLICACAO DOS LIVROS

SELECT Ano FROM Livro

SELECT MIN(Ano) AS MenorAno FROM Livro
SELECT MAX(Ano) AS MaiorAno FROM Livro

--COUNT  LIVRO POR AUTOR

SELECT a.Nome,COUNT (*) as QtdLivros 
FROM Livro l
JOIN Autor a ON a.id_Autor=l.id_Autor
GROUP BY a.Nome

-- LEN 
SELECT LEN('Maria Eduarda') AS Tamanhostring

--UPPER/LOWER

SELECT UPPER(Nome) FROM Leitor
SELECT LOWER(email) FROM Leitor
--LEFT/RIGHT
SELECT * FROM Livro
SELECT LEFT(titulo,5) AS Primeiros5 FROM Livro
SELECT RIGHT(titulo,5) AS Ultimos5 FROM Livro

-- REPLACE 
SELECT REPLACE(titulo,'menina','garota')
FROM Livro


-- CHARINDEX
SELECT titulo,CHARINDEX('que',titulo) AS Posicaoque
FROM Livro

--CONCAT
--CONCATENAR TEXTOS ,JUNTAR DOIS TEXTOS
SELECT CONCAT ('Emprestimo ',e.id_Emprestimo,'-Leitor:',le.nome,'-Livro:',li.titulo) AS Descricao
FROM Emprestimo e 
JOIN Leitor le ON le.id_Leitor = e.id_Leitor
JOIN Livro li ON li.id_Livro =e.id_Livro

---SUBSTRIMG 
SELECT SUBSTRING(titulo,1,10)
FROM Livro
--RTRIM /LTRIM
--REMOVE ESPACOS A ESQUERDA/DIREITA
SELECT Nome,LTRIM(RTRIM(Nome)),trim(Nome)
FROM Leitor
--GETDATE
SELECT GETDATE()

--DATEADD
SELECT id_Emprestimo ,data_emprestimo,DATEADD(DAY,7,data_Emprestimo ) AS PrevisaoDevolucao
FROM Emprestimo


--DIMINUINDO TEMPO
SELECT id_Emprestimo ,data_emprestimo,DATEADD(DAY,-1,data_Emprestimo ) AS PrevisaoDevolucao
FROM Emprestimo

--DATEDIFF: diferenca entre datas
SELECT id_Emprestimo,data_Emprestimo,data_Devolucao,
DATEDIFF(DAY,data_Emprestimo,ISNULL(data_devolucao,GETDATE()))AS DiasComlivro
FROM Emprestimo

--FROMAT :FORMATAR DATAS

SELECT FORMAT(data_Emprestimo,'dd/MM/yyyy') AS Emprestimo,
FORMAT (data_Devolucao,'dd/MM/yy')
FROM Emprestimo

---YEAR()/MONTH()/DAY()
SELECT YEAR(data_emprestimo)AS Ano,
MONTH(data_emprestimo) AS Mes,
DAY(data_emprestimo) AS Dia
FROM Emprestimo

select data_emprestimo FROM Emprestimo

--DATEPART/DATENAME 
SELECT DATEPART(YEAR,data_emprestimo)AS Ano,
DATEPART(WEEKDAY,data_emprestimo)AS DiaSemana,
DATENAME(MONTH,data_emprestimo) AS NomeMes,
DATENAME(WEEKDAY,data_emprestimo)AS NomeDiaSemana
FROM Emprestimo

--- OPRTADORES DE COMPARACAO (IGUALDADE)=
SELECT titulo,ano
FROM Livro
WHERE ano =2016

--DIFERENTE

SELECT nome,email
FROM Leitor
WHERE email NOT LIKE ''


---MAIOR QUE >

SELECT titulo,ano
FROM Livro
WHERE ano> 1900

-- MENOR QUE <
SELECT titulo,ano
FROM Livro
WHERE ano < 1900

-- MAIOR OU IGUAL >=
SELECT id_Emprestimo,data_Emprestimo
FROM Emprestimo
WHERE data_emprestimo >= '2025-09-01'

--MENOR OU IGUAL<=

SELECT id_Emprestimo,data_Emprestimo
FROM Emprestimo
WHERE data_emprestimo >= '2025-08-31'

--OPERADORES LOGICOS
-- AND(e)

SELECT e.id_emprestimo,l.nome, e.data_emprestimo,e.data_devolucao
FROM Emprestimo e
JOIN Leitor l ON l.id_Leitor = e.id_Leitor
WHERE MONTH(e.data_emprestimo) = 9
AND YEAR (e.data_emprestimo)=2025;

--OR(OU)
SELECT titulo ,ano
FROM Livro li
JOIN Autor a ON a.id_Autor =li.id_Autor
WHERE a.Nome ='Maurice Leblanc'
OR a.nome='Jenna Evans'

-- NOT (NEGACAO)
SELECT titulo,ano
FROM Livro li
JOIN Autor a ON a.id_Autor =li.id_Autor
WHERE NOT a.Nome='AMOR & GELATO'

--OPERADORES ESPECIAS
--BETWEEN (ENTRE)
SELECT titulo,ano
FROM Livro
WHERE ano BETWEEN 1800 AND 2000

-- IN(LISTA DE VALORES)
SELECT * FROM Autor
WHERE nome IN ('Jenna Evans','Maurice Leblanc')

---LIKE 
SELECT titulo 
FROM Livro
WHERE titulo LIKE 'O%'
--PORCENTAGEM ANTES DA LETRA - TEM TEXTO ANTES DAQUELA LETRA
--PORCENTAGEM DESPOIS DA LETRA - TEM TEXTO DEPOIS DAQUELA LETRA

---IS NULL
SELECT id_emprestimo ,id_livro,data_Emprestimo
FROM Emprestimo
WHERE data_devolucao IS NULL

-- IS NOT NULL
SELECT id_emprestimo ,id_livro,data_Emprestimo
FROM Emprestimo
WHERE data_devolucao IS NOT NULL


