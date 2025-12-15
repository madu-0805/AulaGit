CREATE DATABASE Futebol;

USE Futebol;

CREATE TABLE Tecnico(
Id_tec INT PRIMARY KEY,
Nome VARCHAR(40)NOT NULL
);
CREATE TABLE EquipedeFutebol(
Id_equipe INT PRIMARY KEY,
Nome VARCHAR UNIQUE NOT NULL,
Id_tec INT FOREIGN KEY REFERENCES Tecnico(Id_tec)
);
CREATE TABLE Jogador(
Id_jog INT PRIMARY KEY,
Nome VARCHAR (40) NOT NULL,
Id_equipe INT FOREIGN KEY  REFERENCES EquipedeFutebol (Id_equipe)
);

CREATE TABLE Partida(
Id_part INT PRIMARY KEY,
Mandante INT,
Visitante INT,
DataPartida DATE NOT NULL
);

SELECT * FROM Tecnico
SELECT * FROM EquipedeFutebol
SELECT * FROM Jogador


INSERT INTO Tecnico (nome) VALUES 
('Deigo Santos'),
('Ravi Carvalho'),
('Matteo de Sa'),
('Mariana SouzA'),
('Fernanda Lima');


INSERT INTO EquipedeFutebol(nome,id_tec) VALUES 
('Flamengo', 1),
('Palmeiras', 2),
('Corinthians', 3),
('Santos', 4),
('Sao Paulo', 5);

INSERT INTO Jogador(Nome,Id_equipe) VALUES

('Gabriel Barbosa', 5),
('Bruno Henrique', 4),
('Everton Ribeiro', 3),
('Diego Alves', 2),
('Arrascaeta', 1);


INSERT INTO Partida (mandante, visitante, DataPartida) VALUES
(1, 2, '2025-09-10'),
(3, 4, '2025-09-11'),
(5, 1, '2025-09-12'),
(2, 3, '2025-09-13'),
(4, 5, '2025-09-14');