CREATE DATABASE clinica2;

USE clinica2;

CREATE TABLE Paciente (
CPF VARCHAR (14) PRIMARY KEY,
Nome VARCHAR(40),
Telefone VARCHAR(30),
Numero_Plano INT,
Nome_Plano VARCHAR(20),
Tipo_Plano VARCHAR(10)
);

CREATE TABLE Medico(
CRM INT PRIMARY KEY,
NomeMedico VARCHAR(30),
Especialidade VARCHAR(20)
);

CREATE TABLE Consulta(
NumeroConsulta INT PRIMARY KEY IDENTITY,
DataConsulta DATE,
HorarioConsulta TIME,
CPFPaciente VARCHAR(14) FOREIGN KEY  REFERENCES Paciente(CPF),
CRMMedico INT FOREIGN KEY REFERENCES Medico(CRM)
);

SELECT * FROM Paciente
SELECT * FROM Consulta
SELECT * FROM Medico

-- INSERIR PACIENTES
INSERT INTO Paciente (CPF, Nome, Telefone, Numero_Plano, Nome_Plano, Tipo_Plano) VALUES 
('111.111.111-11', 'Maria Silva', '11987654321', 1001, 'SaudeMais', 'Ouro'),
('222.222.222-22', 'João Souza', '11912345678', 1002, 'VidaPlena', 'Prata'),
('333.333.333-33', 'Ana Costa', '21965432100', 1003, 'SaudeTop', 'Bronze'),
('444.444.444-44', 'Carlos Pereira', '31988776655', 1004, 'SaudeMais', 'Ouro'),
('555.555.555-55', 'Fernanda Alves', '21988887777', 1005, 'VidaPlena', 'Prata'),
('666.666.666-66', 'Roberto Dias', '11933332222', 1006, 'SaudeTop', 'Bronze');

-- INSERIR MÉDICOS
INSERT INTO Medico (CRM, NomeMedico, Especialidade)VALUES
(101, 'Dr. Pedro Ramos', 'Cardiologia'),
(102, 'Dra. Julia Fernandes', 'Dermatologia'),
(103, 'Dr. Marcos Lima', 'Ortopedia'),
(104, 'Dra. Camila Nogueira', 'Pediatria'),
(105, 'Dr. Henrique Martins', 'Gastroenterologia');

-- INSERIR CONSULTAS
INSERT INTO Consulta (DataConsulta, HorarioConsulta, CRMMedico, CPFPaciente)
VALUES
('2025-09-01', '09:00', 101, '111.111.111-11'), -- Maria com Dr. Pedro
('2025-09-01', '10:30', 102, '222.222.222-22'), -- João com Dra. Julia
('2025-09-02', '14:00', 103, '333.333.333-33'), -- Ana com Dr. Marcos
('2025-09-03', '08:30', 101, '444.444.444-44'); -- Carlos com Dr. Pedro


-- JOIN

--INEER JOIN/JOIN
SELECT c.NumeroConsulta, c.DataConsulta ,c.HorarioConsulta ,p.Nome AS NomePaciente, m.NomeMedico, m.Especialidade

FROM Consulta c
INNER JOIN Paciente p ON c.CPFPaciente = p.CPF
INNER JOIN Medico m ON c. CRMMedico = m.CRM

SELECT p.Nome AS NOME_PACIENTE, c.DataConsulta, c.HorarioConsulta, m.NomeMedico,c.CRMMedico-- thiago explicacao 
FROM Consulta c
INNER JOIN Paciente p ON c.CPFPaciente = p.CPF
INNER JOIN Medico m ON c.CRMMedico = m.CRM 


--    LEFT JOIN 
SELECT p.Nome AS NomePaciente, c.DataConsulta, m.NomeMedico 
FROM Paciente p
LEFT JOIN Consulta c ON p.CPF = c.CPFPaciente
LEFT JOIN Medico m ON c.CRMMedico = m.CRM


--RIGHT JOIN --
SELECT m.NomeMedico, m.Especialidade,c.DataConsulta--, p.Nome
FROM Consulta c
RIGHT JOIN Medico m ON c.CRMMedico=m.CRM


-- FULL JOIN 
SELECT p.Nome , m.NomeMedico ,c.DataConsulta
FROM Paciente p
FULL JOIN Consulta c ON p.CPF =c.CPFPaciente
FULL JOIN Medico m ON c.CRMMedico =m.CRM


-- CROSS JOIN 
SELECT p.Nome, m.NomeMedico, m.Especialidade
FROM Paciente p 
CROSS JOIN Medico m


SELECT p.Nome AS NomePaciente, m.NomeMedico, 'Disponível' AS SITUACAO
FROM Paciente p
CROSS JOIN Medico m