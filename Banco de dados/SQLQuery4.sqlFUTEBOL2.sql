CREATE DATABASE Futebol2;
USE Futebol2;

CREATE TABLE Tecnico(
Id_tec INT PRIMARY KEY,
Nome VARCHAR(40)
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

INSERT INTO Tecnico (Id_tec, Nome) VALUES
(1, 'Deigo Santos'),
(2, 'Ravi Carvalho'),
(3, 'Matteo de Sa'),
(4, 'Mariana Souza'),
(5, 'Fernanda Lima');

INSERT INTO EquipedeFutebol (Id_equipe, Nome, Id_tec) VALUES
(1, 'Flamengo', 1),
(2, 'Palmeiras', 2),
(3, 'Corinthians', 3),
(4, 'Santos', 4),
(5, 'Sao Paulo', 5);

INSERT INTO Jogador (Id_jog, Nome, Id_equipe) VALUES
(1, 'Gabriel Barbosa', 1),
(2, 'Bruno Henrique', 5),
(3, 'Everton Ribeiro', 2),
(4, 'Diego Alves', 4),
(5, 'Arrascaeta', 3);



INSERT INTO Partida (Id_part, Mandante, Visitante, DataPartida) VALUES
(1, 1, 2, '2025-09-10'),
(2, 3, 4, '2025-09-11'),
(3, 5, 1, '2025-09-12'),
(4, 2, 3, '2025-09-13'),
(5, 4, 5, '2025-09-14');

 SELECT t.Nome AS Tecnico,e.Nome AS Equipe,j.Nome AS Jogador
FROM Tecnico t
CROSS JOIN EquipedeFutebol e
CROSS JOIN Jogador j;