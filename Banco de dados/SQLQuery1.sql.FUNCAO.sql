----------------------------------------------------
-- ?? FUNÇÕES DE AGREGAÇÃO
-----------------------------------------------------
-- Quantidade total de leitores
SELECT COUNT(*) AS QtdLeitores
FROM Leitor;

-- Empréstimos por leitor
SELECT l.Nome AS Leitor,
       COUNT(e.id_Emprestimo) AS QtdEmprestimos
FROM Emprestimo e
JOIN Leitor l ON l.id_Leitor = e.id_Leitor
GROUP BY l.Nome
ORDER BY QtdEmprestimos DESC;

-- Ano mínimo e máximo de publicação dos livros
SELECT MIN(Ano) AS MenorAno, 
       MAX(Ano) AS MaiorAno
FROM Livro;

-- Quantidade de livros por autor
SELECT a.Nome, COUNT(*) AS QtdLivros 
FROM Livro l
JOIN Autor a ON a.id_Autor = l.id_Autor
GROUP BY a.Nome;
-----------------------------------------------------
-- ?? FUNÇÕES DE STRING
-----------------------------------------------------

-- Tamanho de string
SELECT LEN('Maria Eduarda') AS TamanhoString;

-- Maiúsculo / Minúsculo
SELECT UPPER(Nome) AS NomeMaiusculo FROM Leitor;
SELECT LOWER(Email) AS EmailMinusculo FROM Leitor;

-- Primeiros e últimos 5 caracteres
SELECT LEFT(Titulo, 5) AS Primeiros5,
       RIGHT(Titulo, 5) AS Ultimos5
FROM Livro;

-- Substituir palavras
SELECT REPLACE(Titulo, 'menina', 'garota') AS NovoTitulo
FROM Livro;

-- Posição de substring
SELECT Titulo, CHARINDEX('que', Titulo) AS PosicaoQue
FROM Livro;

-- Concatenar textos
SELECT CONCAT('Empréstimo ', e.id_Emprestimo,
              ' - Leitor: ', le.Nome,
              ' - Livro: ', li.Titulo) AS Descricao
FROM Emprestimo e 
JOIN Leitor le ON le.id_Leitor = e.id_Leitor
JOIN Livro li ON li.id_Livro = e.id_Livro;

-- Substring
SELECT SUBSTRING(Titulo, 1, 10) AS InicioTitulo
FROM Livro;

-- Remover espaços
SELECT Nome,
       LTRIM(RTRIM(Nome)) AS NomeSemEspacos,
       TRIM(Nome) AS NomeLimpo
FROM Leitor;
-----------------------------------------------------
-- ?? FUNÇÕES DE DATA
-----------------------------------------------------
-- Data atual
SELECT GETDATE() AS DataAtual;

-- Adicionar/Deduzir dias
SELECT id_Emprestimo, Data_Emprestimo,
       DATEADD(DAY, 7, Data_Emprestimo) AS PrevisaoDevolucao
FROM Emprestimo;

SELECT id_Emprestimo, Data_Emprestimo,
       DATEADD(DAY, -1, Data_Emprestimo) AS DiaAnterior
FROM Emprestimo;

-- Diferença entre datas
SELECT id_Emprestimo, Data_Emprestimo, Data_Devolucao,
       DATEDIFF(DAY, Data_Emprestimo, ISNULL(Data_Devolucao, GETDATE())) AS DiasComLivro
FROM Emprestimo;

-- Formatar datas
SELECT FORMAT(Data_Emprestimo, 'dd/MM/yyyy') AS Emprestimo,
       FORMAT(Data_Devolucao, 'dd/MM/yy')   AS Devolucao
FROM Emprestimo;

-- Ano, mês e dia
SELECT YEAR(Data_Emprestimo) AS Ano,
       MONTH(Data_Emprestimo) AS Mes,
       DAY(Data_Emprestimo) AS Dia
FROM Emprestimo;

-- Partes da data e nomes
SELECT DATEPART(YEAR, Data_Emprestimo) AS Ano,
       DATEPART(WEEKDAY, Data_Emprestimo) AS DiaSemana,
       DATENAME(MONTH, Data_Emprestimo) AS NomeMes,
       DATENAME(WEEKDAY, Data_Emprestimo) AS NomeDiaSemana
FROM Emprestimo;
-----------------------------------------------------
-- ?? OPERADORES DE COMPARAÇÃO
-----------------------------------------------------
-- Igualdade
SELECT Titulo, Ano
FROM Livro
WHERE Ano = 2016;

-- Diferente (email não vazio)
SELECT Nome, Email
FROM Leitor
WHERE Email NOT LIKE '';

-- Maior que
SELECT Titulo, Ano
FROM Livro
WHERE Ano > 1900;

-- Menor que
SELECT Titulo, Ano
FROM Livro
WHERE Ano < 1900;

-- Maior ou igual
SELECT id_Emprestimo, Data_Emprestimo
FROM Emprestimo
WHERE Data_Emprestimo >= '2025-09-01';

-- Menor ou igual
SELECT id_Emprestimo, Data_Emprestimo
FROM Emprestimo
WHERE Data_Emprestimo <= '2025-08-31';
-----------------------------------------------------
-- ?? OPERADORES LÓGICOS
-----------------------------------------------------
-- AND
SELECT e.id_Emprestimo, l.Nome, e.Data_Emprestimo, e.Data_Devolucao
FROM Emprestimo e
JOIN Leitor l ON l.id_Leitor = e.id_Leitor
WHERE MONTH(e.Data_Emprestimo) = 9
  AND YEAR(e.Data_Emprestimo) = 2025;

-- OR
SELECT li.Titulo, li.Ano
FROM Livro li
JOIN Autor a ON a.id_Autor = li.id_Autor
WHERE a.Nome = 'Maurice Leblanc'
   OR a.Nome = 'Jenna Evans';

-- NOT
SELECT li.Titulo, li.Ano
FROM Livro li
JOIN Autor a ON a.id_Autor = li.id_Autor
WHERE NOT a.Nome = 'AMOR & GELATO';
-----------------------------------------------------
-- ?? OPERADORES ESPECIAIS
-----------------------------------------------------

-- BETWEEN
SELECT Titulo, Ano
FROM Livro
WHERE Ano BETWEEN 1800 AND 2000;

-- IN
SELECT * 
FROM Autor
WHERE Nome IN ('Jenna Evans', 'Maurice Leblanc');

-- LIKE
SELECT Titulo 
FROM Livro
WHERE Titulo LIKE 'O%';

-- IS NULL
SELECT id_Emprestimo, id_Livro, Data_Emprestimo
FROM Emprestimo
WHERE Data_Devolucao IS NULL;

-- IS NOT NULL
SELECT id_Emprestimo, id_Livro, Data_Emprestimo
FROM Emprestimo
WHERE Data_Devolucao IS NOT NULL;
