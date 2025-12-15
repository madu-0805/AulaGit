--Cadastro de Funcionários
CREATE TABLE Funcionarios (
    IdFunc INT PRIMARY KEY,
    Nome VARCHAR(100),
    Cargo VARCHAR(50),
    Salario DECIMAL(10,2)
);


INSERT INTO Funcionarios( IdFunc,  Nome,Cargo,Salario) VALUES
(1, 'Lucas Andrade', 'Gerente', 5000.00),
(2, 'Mariana Costa', 'Analista', 3200.00),
(3, 'Pedro Lima', 'Estagiário', 1500.00),
(4, 'Juliana Souza', 'Desenvolvedor', 4000.00),
(5, 'Ricardo Mendes', 'Designer', 2800.00);

SELECT * FROM Funcionarios 
WHERE Salario > 3000; 

SELECT * FROM Funcionarios
WHERE Cargo = 'Analista';
SELECT Nome, Cargo FROM Funcionarios; 