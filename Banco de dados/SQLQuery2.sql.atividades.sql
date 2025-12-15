--Desafios da Biblioteca

--1 )Quantos livros existem cadastrados na biblioteca?
SELECT COUNT (*) AS total_livros
FROM Livro;

--2)Qual é o ano médio de publicação dos livros?
SELECT AVG(ano) AS ano_medio
FROM livro;

--3)Qual leitor fez o maior número de empréstimos?
SELECT l.nome, COUNT(e.id_Emprestimo) AS total_emprestimos
FROM emprestimo e
JOIN leitor l ON e.id_leitor = l.id_Leitor
GROUP BY l.nome
ORDER BY total_emprestimos DESC



--Funções de Texto
-- 1) Mostre os 3 primeiros caracteres de todos os nomes de autores.
SELECT SUBSTRING(nome, 1, 3) AS iniciais
FROM autor;

--2)Exiba os títulos de livros com todas as letras em minúsculo.

SELECT LOWER(titulo) AS titulo_minusculo
FROM livro;

--3)Mostre apenas os leitores cujo e-mail termina com .com.
SELECT nome,email
FROM Leitor
WHERE email NOT LIKE 'com'

--4) Substitua a palavra “menina” por “moca” no título do livro Markus Zusak
SELECT REPLACE(l.titulo, 'menina', 'Moça ') AS titulo_editado
FROM livro  l
JOIN autor a ON l.id_autor = a.id_Autor
WHERE a.nome = 'Markus Zusak';






-- Funções de Data e Hora
--1)Mostre os empréstimos realizados no mês de agosto de 2025 (mostrar número do mês).
SELECT id_Emprestimo, id_livro, id_leitor,
MONTH(data_emprestimo) AS mes
FROM emprestimo
WHERE YEAR(data_emprestimo) = 2025
AND MONTH(data_emprestimo) = 8;

--2)Calcule quantos dias se passaram desde o primeiro empréstimo registrado até hoje.

SELECT id_Emprestimo,data_Emprestimo,data_Devolucao,
DATEDIFF(DAY,data_Emprestimo,ISNULL(data_devolucao,GETDATE()))AS DiasComlivro
FROM Emprestimo;

--3)Mostre a data do empréstimo e o nome do dia da semana em que ele aconteceu.
SELECT DATEPART(YEAR,data_emprestimo)AS Ano,
DATEPART(WEEKDAY,data_emprestimo)AS DiaSemana,
DATENAME(WEEKDAY,data_emprestimo)AS NomeDiaSemana
FROM Emprestimo;

--- Operadores de Comparação e Lógicos

--1)Liste os livros publicados entre 1950 e 2005, mas que não sejam de Markus Zusak.
SELECT l.titulo, l.ano,a.nome
FROM livro l
JOIN autor a ON l.id_autor = a.id_Autor
WHERE l.ano BETWEEN 1907 AND 2005
AND a.nome <> 'Markus Zusak';

--2)Mostre todos os leitores que têm nome começando com a letra “C”.
SELECT *FROM Leitor
WHERE Nome LIKE 'G%'

--3)Mostre os empréstimos que aconteceram em 2025, mas ainda não foram devolvidos.
SELECT * FROM emprestimo
WHERE YEAR(data_emprestimo) = 2025
AND data_devolucao >GETDATE();

--4. Liste os autores que não têm nenhum livro cadastrado no banco.
SELECT a.nome
FROM autor a
LEFT JOIN livro l ON a.id_Autor = l.id_autor
WHERE l.id_Livro IS NULL;