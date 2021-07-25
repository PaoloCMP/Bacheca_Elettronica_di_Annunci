-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `mydb` ;

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET utf8 ;
USE `mydb` ;

-- -----------------------------------------------------
-- Table `mydb`.`Categoria`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Categoria` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Categoria` (
  `Nome` VARCHAR(45) NOT NULL,
  `Categoria_Nome` VARCHAR(45) NULL,
  PRIMARY KEY (`Nome`),
  INDEX `fk_Categoria_Categoria1_idx` (`Categoria_Nome` ASC) VISIBLE,
  CONSTRAINT `fk_Categoria_Categoria1`
    FOREIGN KEY (`Categoria_Nome`)
    REFERENCES `mydb`.`Categoria` (`Nome`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Utente`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Utente` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Utente` (
  `Username` VARCHAR(45) NOT NULL,
  `Nome` VARCHAR(45) NOT NULL,
  `Cognome` VARCHAR(45) NOT NULL,
  `IndirizzoResidenza` VARCHAR(45) NOT NULL,
  `IndirizzoFatturazione` VARCHAR(45) NULL,
  `NumeroCC` BIGINT(16) NULL,
  `ScadenzaCC` VARCHAR(45) NULL,
  `Pass_word` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Username`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Annuncio`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Annuncio` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Annuncio` (
  `idAnnuncio` INT NOT NULL AUTO_INCREMENT,
  `Descrizione` VARCHAR(1000) NOT NULL,
  `Foto` MEDIUMBLOB NULL,
  `UltimaModifica` VARCHAR(45) NOT NULL,
  `Stato` VARCHAR(45) NOT NULL,
  `Categoria_Nome` VARCHAR(45) NOT NULL,
  `Utente_Username` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`idAnnuncio`),
  INDEX `fk_Annuncio_Categoria_idx` (`Categoria_Nome` ASC) VISIBLE,
  INDEX `fk_Annuncio_Utente1_idx` (`Utente_Username` ASC) VISIBLE,
  CONSTRAINT `fk_Annuncio_Categoria`
    FOREIGN KEY (`Categoria_Nome`)
    REFERENCES `mydb`.`Categoria` (`Nome`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Annuncio_Utente1`
    FOREIGN KEY (`Utente_Username`)
    REFERENCES `mydb`.`Utente` (`Username`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
COMMENT = '		';


-- -----------------------------------------------------
-- Table `mydb`.`Contatto`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Contatto` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Contatto` (
  `Recapito` VARCHAR(45) NOT NULL,
  `Utente_Username` VARCHAR(45) NOT NULL,
  `Tipo` VARCHAR(45) NOT NULL,
  `Preferito` INT NULL,
  PRIMARY KEY (`Recapito`),
  INDEX `fk_Contatto_Utente1_idx` (`Utente_Username` ASC) VISIBLE,
  CONSTRAINT `fk_Contatto_Utente1`
    FOREIGN KEY (`Utente_Username`)
    REFERENCES `mydb`.`Utente` (`Username`)
    ON DELETE CASCADE
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Segue`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Segue` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Segue` (
  `Annuncio_idAnnuncio` INT NOT NULL,
  `Follower` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Annuncio_idAnnuncio`, `Follower`),
  INDEX `fk_Annuncio_has_Utente_Utente1_idx` (`Follower` ASC) VISIBLE,
  INDEX `fk_Annuncio_has_Utente_Annuncio1_idx` (`Annuncio_idAnnuncio` ASC) VISIBLE,
  CONSTRAINT `fk_Annuncio_has_Utente_Annuncio1`
    FOREIGN KEY (`Annuncio_idAnnuncio`)
    REFERENCES `mydb`.`Annuncio` (`idAnnuncio`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Annuncio_has_Utente_Utente1`
    FOREIGN KEY (`Follower`)
    REFERENCES `mydb`.`Utente` (`Username`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Venduto`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Venduto` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Venduto` (
  `Prezzo` INT NOT NULL,
  `Riscossione` INT NOT NULL,
  `Annuncio_idAnnuncio` INT NOT NULL,
  PRIMARY KEY (`Annuncio_idAnnuncio`),
  CONSTRAINT `fk_Venduto_Annuncio1`
    FOREIGN KEY (`Annuncio_idAnnuncio`)
    REFERENCES `mydb`.`Annuncio` (`idAnnuncio`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Messaggio`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Messaggio` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Messaggio` (
  `idMessaggio` INT NOT NULL AUTO_INCREMENT,
  `Testo` VARCHAR(1000) NOT NULL,
  `Mittente_Username` VARCHAR(45) NOT NULL,
  `Annuncio_idAnnuncio` INT NOT NULL,
  `Destinatario_Username` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`idMessaggio`),
  INDEX `fk_Messaggio_Utente1_idx` (`Mittente_Username` ASC) VISIBLE,
  INDEX `fk_Messaggio_Annuncio1_idx` (`Annuncio_idAnnuncio` ASC) VISIBLE,
  INDEX `fk_Messaggio_Utente2_idx` (`Destinatario_Username` ASC) VISIBLE,
  CONSTRAINT `fk_Messaggio_Utente1`
    FOREIGN KEY (`Mittente_Username`)
    REFERENCES `mydb`.`Utente` (`Username`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Messaggio_Annuncio1`
    FOREIGN KEY (`Annuncio_idAnnuncio`)
    REFERENCES `mydb`.`Annuncio` (`idAnnuncio`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Messaggio_Utente2`
    FOREIGN KEY (`Destinatario_Username`)
    REFERENCES `mydb`.`Utente` (`Username`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Domanda`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Domanda` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Domanda` (
  `idDomanda` INT NOT NULL AUTO_INCREMENT,
  `Testo` VARCHAR(1000) NOT NULL,
  `Utente_Username` VARCHAR(45) NOT NULL,
  `Annuncio_idAnnuncio` INT NOT NULL,
  PRIMARY KEY (`idDomanda`),
  INDEX `fk_Domanda_Utente1_idx` (`Utente_Username` ASC) VISIBLE,
  INDEX `fk_Domanda_Annuncio1_idx` (`Annuncio_idAnnuncio` ASC) VISIBLE,
  CONSTRAINT `fk_Domanda_Utente1`
    FOREIGN KEY (`Utente_Username`)
    REFERENCES `mydb`.`Utente` (`Username`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Domanda_Annuncio1`
    FOREIGN KEY (`Annuncio_idAnnuncio`)
    REFERENCES `mydb`.`Annuncio` (`idAnnuncio`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

USE `mydb` ;

-- -----------------------------------------------------
-- Placeholder table for view `mydb`.`annunciSeguiti`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`annunciSeguiti` (`idAnnuncio` INT, `Descrizione` INT, `Foto` INT, `UltimaModifica` INT, `Stato` INT, `Categoria_Nome` INT, `Utente_Username` INT, `Follower` INT);

-- -----------------------------------------------------
-- Placeholder table for view `mydb`.`Reports`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Reports` (`Utente` INT, `Annunci_Totale` INT, `Importo` INT, `NumeroCC` INT, `ScadenzaCC` INT);

-- -----------------------------------------------------
-- procedure segnaRiscosso
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`segnaRiscosso`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `segnaRiscosso` ()
BEGIN
	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
	START TRANSACTION;
		BEGIN					
            UPDATE VENDUTO 
				SET Riscossione = 1
                WHERE Annuncio_idAnnuncio in (SELECT Annuncio_idAnnuncio
											  FROM REPORTS);
		END;
	COMMIT;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure creaCategoria
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`creaCategoria`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `creaCategoria` (IN nameCategoria VARCHAR(45), IN categoriaDipendente VARCHAR(45), IN chek INT)  
BEGIN
		IF (chek = 1) THEN
			START TRANSACTION;
			BEGIN        
			INSERT INTO Categoria VALUES (nameCategoria, categoriaDipendente);
            COMMIT;
            END;
		ELSE
			START TRANSACTION;
			BEGIN
            INSERT INTO Categoria (Nome) VALUES (nameCategoria);
            COMMIT;
            END;
		END IF;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure vediReport
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`vediReport`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `vediReport` ()
BEGIN
	Select Utente, Annunci_Totale, Importo, NumeroCC, ScadenzaCC  From Reports;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure registraUtente
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`registraUtente`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `registraUtente` (IN username VARCHAR(45), IN nome VARCHAR(45), IN cognome VARCHAR(45), IN indirizzoResi VARCHAR(45), IN indirizzoFatt VARCHAR(45), IN numCC BIGINT(16), IN scadCC VARCHAR(45), IN chek INT, IN tipo VARCHAR(45), IN recap VARCHAR(45),IN passwordd VARCHAR(45))
BEGIN
	if (chek = 0) then
		start transaction;
		begin 
			insert into Utente values (username, nome, cognome, indirizzoResi, indirizzoFatt, numCC, scadCC, MD5(passwordd));
			insert into Contatto values (recap, username, tipo, 1);
        commit;
		end;
        end if;
	if (chek = 1) then
		start transaction;
		begin
			insert into Utente (Username, Nome, Cognome, IndirizzoResidenza, IndirizzoFatturazione,pass_word) values (username, nome, cognome, indirizzoResi, indirizzoFatt,MD5(passwordd));
			insert into Contatto values (recap, username, tipo, 1);
        commit;
        end;
        end if;
	if (chek = 2) then
		start transaction;
		begin
			insert into Utente (Username, Nome, Cognome, IndirizzoResidenza, NumeroCC, ScadenzaCC, pass_word) values (username, nome, cognome, indirizzoResi, numCC, scadCC, MD5(passwordd));
			insert into Contatto values (recap, username, tipo, 1);
        commit;
        end;
        end if;
	if (chek = 3) then
		start transaction;
		begin
			insert into Utente (Username, Nome, Cognome, IndirizzoResidenza, pass_word) values (username, nome, cognome, indirizzoResi, MD5(passwordd));
			insert into Contatto values (recap, username, tipo, 1);

        commit;
        end;
        end if;
	
	
    	
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure registraRecapito
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`registraRecapito`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `registraRecapito` (IN recapito VARCHAR(45), IN usernam VARCHAR(45), IN tipo VARCHAR(45))
BEGIN
	start transaction;
        begin 
			insert into Contatto values (recapito, usernam, tipo, 0);
		commit;
        end;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure bacheca
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`bacheca`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `bacheca` ()
BEGIN
	SELECT idAnnuncio, Descrizione, Foto, Categoria_Nome, Utente_Username FROM ANNUNCIO WHERE stato = 'vendita';
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure rimuoviAnnuncio
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`rimuoviAnnuncio`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `rimuoviAnnuncio` (IN orario VARCHAR(45), IN idAnn INT, IN Autore VARCHAR(45))
BEGIN
	if (Autore <> (Select Utente_Username from Annuncio Where idAnnuncio = idAnn)) then
		signal sqlstate '45000'
		SET MESSAGE_TEXT = 'Non sei abilitato alla modifica di questo annuncio';        
	else
		Update Annuncio Set Stato = 'rimosso', UltimaModifica = orario Where idAnnuncio = idAnn;
	end if;
    
    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure vediAnnunciSeguiti
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`vediAnnunciSeguiti`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `vediAnnunciSeguiti` (IN Follow VARCHAR(45))
BEGIN
	Select idAnnuncio, Descrizione, UltimaModifica, Stato, Categoria_Nome, Utente_Username From annunciSeguiti Where Follower = Follow;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure inviaMessaggio
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`inviaMessaggio`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `inviaMessaggio` (IN mess VARCHAR(1000), IN mittente VARCHAR(45), IN idAnn INT, IN destinatario VARCHAR(45))
BEGIN
	
		Insert into Messaggio Values (Null, mess, mittente, idAnn, destinatario);
	
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure segnaVenduto
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`segnaVenduto`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `segnaVenduto` (IN orario VARCHAR(45), IN idAnn INT, IN Autore VARCHAR(45), IN prezzo INT)
BEGIN
	if (Autore <> (Select Utente_Username from Annuncio Where idAnnuncio = idAnn)) then
		signal sqlstate '45000'
		SET MESSAGE_TEXT = 'Non sei abilitato alla modifica di questo annuncio';        
	else
		start transaction;
		UPDATE Annuncio 
SET 
    Stato = 'venduto',
    UltimaModifica = orario
WHERE
    idAnnuncio = idAnn;
        Insert into Venduto Values (prezzo, 0, idAnn);
        commit;
	end if;
    
    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure domande
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`domande`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `domande` ()
BEGIN
	SELECT idDomanda, Testo, Utente_Username, Annuncio_idannuncio  FROM Domanda WHERE Annuncio_idAnnuncio IN (SELECT idAnnuncio FROM Annuncio WHERE Stato = 'vendita') ORDER BY idDomanda;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure inserisciAnnuncio
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`inserisciAnnuncio`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `inserisciAnnuncio` (IN categ VARCHAR(45), IN username VARCHAR(45), IN photo mediumblob, IN chek VARCHAR(3), IN orario VARCHAR(45), IN descrizione VARCHAR(45))
BEGIN
	start transaction;
		if (chek = 'si') then
			insert into Annuncio values (Null, descrizione, photo, orario, 'vendita', categ, username);
		else if (chek = 'no') then 
			insert into Annuncio (Descrizione, UltimaModifica, Stato, Categoria_Nome, Utente_Username) values (descrizione, orario, 'vendita', categ, username);
		end if;
        end if;
	commit;
    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure categorie
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`categorie`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `categorie` ()
BEGIN
	select Nome, Categoria_Nome from Categoria;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure checkUser
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`checkUser`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `checkUser` (IN user VARCHAR(45), pass VARCHAR(45))
BEGIN
	if (user not in (Select Username from Utente)) then
		signal sqlstate '45000'
		SET MESSAGE_TEXT = 'Non registrato';        
	end if;
    if (MD5(pass) <> (Select Pass_word from Utente where user = Username)) then 
		signal sqlstate '45000'
		SET MESSAGE_TEXT = 'Password errata';  
	end if;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure inviaDomanda
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`inviaDomanda`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `inviaDomanda` (IN descrizione VARCHAR(1000), IN mittente VARCHAR(45), IN idAnn INT)
BEGIN
	Insert into Domanda Values (Null, descrizione, mittente, idAnn);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure modificaAnnuncio
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`modificaAnnuncio`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `modificaAnnuncio` (IN descrizione VARCHAR(1000), IN ora VARCHAR(45), IN id INT, IN user VARCHAR(45))
BEGIN
	if (user <> (select Utente_Username from Annuncio where idAnnuncio = id)) then
		signal sqlstate '45000'
		SET MESSAGE_TEXT = 'Non sei abilitato alla modifica di questo annuncio';
	else 
		update Annuncio set Descrizione = descrizione where idAnnuncio = id;
	end if;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure vediMessRicevuti
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`vediMessRicevuti`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `vediMessRicevuti` (IN usern VARCHAR(45))
BEGIN
	select idMessaggio, Testo, Mittente_Username, Annuncio_idAnnuncio from Messaggio Where Destinatario_Username=usern;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure vediMessInviati
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`vediMessInviati`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `vediMessInviati` (IN usern VARCHAR(45))
BEGIN
	select idMessaggio, Testo, Destinatario_Username, Annuncio_idAnnuncio from Messaggio Where Mittente_Username=usern;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure modInfo
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`modInfo`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `modInfo` (IN indirizzoNuovo VARCHAR(45), IN user VARCHAR(45), IN chek INT)
BEGIN
	if (chek = 1) then
		UPDATE Utente SET IndirizzoResidenza = indirizzoNuovo WHERE Username = user;
	end if;
    if (chek = 2) then
		UPDATE Utente SET IndirizzoFatturazione = indirizzoNuovo WHERE Username = user;
	end if;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure modInfoCarta
-- -----------------------------------------------------

USE `mydb`;
DROP procedure IF EXISTS `mydb`.`modInfoCarta`;

DELIMITER $$
USE `mydb`$$
CREATE PROCEDURE `modInfoCarta` (IN scad VARCHAR(45), IN user VARCHAR(45), IN num BIGINT(16))
BEGIN
	UPDATE Utente SET NumeroCC = num, ScadenzaCC = scad WHERE Username = user;
	
END$$

DELIMITER ;

-- -----------------------------------------------------
-- View `mydb`.`annunciSeguiti`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`annunciSeguiti`;
DROP VIEW IF EXISTS `mydb`.`annunciSeguiti` ;
USE `mydb`;
CREATE  OR REPLACE VIEW `annunciSeguiti` AS
    SELECT 
        idAnnuncio,
        Descrizione,
        Foto,
        UltimaModifica,
        Stato,
        Categoria_Nome,
        Annuncio.Utente_Username,
        Follower
    FROM
        Segue
            JOIN
        Annuncio ON Annuncio_idAnnuncio = idAnnuncio;

-- -----------------------------------------------------
-- View `mydb`.`Reports`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Reports`;
DROP VIEW IF EXISTS `mydb`.`Reports` ;
USE `mydb`;
CREATE  OR REPLACE VIEW `Reports` AS
    SELECT 
        Utente_Username AS Utente,
        COUNT(*) AS Annunci_Totale ,
        (SUM(Prezzo) * 0.03) AS Importo,
        NumeroCC,
        ScadenzaCC
    FROM
        Venduto
            JOIN
        Annuncio ON Annuncio_idAnnuncio = idAnnuncio
            JOIN
        Utente ON Utente_Username = Username
    WHERE
        Riscossione = 0
    GROUP BY Utente_Username , NumeroCC , ScadenzaCC;
USE `mydb`;

DELIMITER $$

USE `mydb`$$
DROP TRIGGER IF EXISTS `mydb`.`Annuncio_BEFORE_INSERT` $$
USE `mydb`$$
CREATE DEFINER = CURRENT_USER TRIGGER `mydb`.`Annuncio_BEFORE_INSERT` BEFORE INSERT ON `Annuncio` FOR EACH ROW
BEGIN
	if NEW.Utente_Username NOT IN (SELECT Username
									FROM Utente
                                    WHERE NumeroCC IS NOT NULL AND ScadenzaCC IS NOT NULL)
	then signal sqlstate '45000'
	SET MESSAGE_TEXT = 'Per inserire un annuncio dovevano essere inseriti i dati della carta di credito';
	end if;
END$$


USE `mydb`$$
DROP TRIGGER IF EXISTS `mydb`.`Messaggio_BEFORE_INSERT` $$
USE `mydb`$$
CREATE DEFINER = CURRENT_USER TRIGGER `mydb`.`Messaggio_BEFORE_INSERT` BEFORE INSERT ON `Messaggio` FOR EACH ROW
BEGIN
		if ((NEW.Destinatario_Username <> (Select Utente_Username
										from Annuncio 
										where idAnnuncio = NEW.Annuncio_idAnnuncio))
				and (NEW.Mittente_Username <> (Select Utente_Username
											from Annuncio 
											where idAnnuncio = NEW.Annuncio_idAnnuncio)))
		then signal sqlstate '45000'
        SET Message_text = 'Impossibile inviare messaggio';
        end if;

END$$


USE `mydb`$$
DROP TRIGGER IF EXISTS `mydb`.`Domanda_BEFORE_INSERT` $$
USE `mydb`$$
CREATE DEFINER = CURRENT_USER TRIGGER `mydb`.`Domanda_BEFORE_INSERT` BEFORE INSERT ON `Domanda` FOR EACH ROW
BEGIN
	if NEW.Annuncio_idAnnuncio NOT IN (SELECT idAnnuncio
									FROM Annuncio
                                    WHERE stato = 'vendita')
	then signal sqlstate '45000'
	SET MESSAGE_TEXT = 'Puoi inserire domande solo su annunci visibili in bacheca';
	end if;
END$$


DELIMITER ;
SET SQL_MODE = '';
DROP USER IF EXISTS gestore;
SET SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';
CREATE USER 'gestore' IDENTIFIED BY 'gestore';

GRANT ALL ON `mydb`.* TO 'gestore';
GRANT ALL ON TABLE `mydb`.`Utente` TO 'gestore';
GRANT ALL ON TABLE `mydb`.`Annuncio` TO 'gestore';
GRANT ALL ON TABLE `mydb`.`Categoria` TO 'gestore';
GRANT ALL ON TABLE `mydb`.`Domanda` TO 'gestore';
GRANT ALL ON TABLE `mydb`.`Messaggio` TO 'gestore';
GRANT ALL ON TABLE `mydb`.`Segue` TO 'gestore';
GRANT ALL ON TABLE `mydb`.`Venduto` TO 'gestore';
GRANT EXECUTE ON procedure `mydb`.`creaCategoria` TO 'gestore';
GRANT ALL ON procedure `mydb`.`segnaRiscosso` TO 'gestore';
GRANT ALL ON procedure `mydb`.`vediReport` TO 'gestore';
GRANT ALL ON TABLE `mydb`.`Reports` TO 'gestore';
SET SQL_MODE = '';
DROP USER IF EXISTS login;
SET SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';
CREATE USER 'login' IDENTIFIED BY 'login';

GRANT ALL ON TABLE `mydb`.`Contatto` TO 'login';
GRANT ALL ON TABLE `mydb`.`Utente` TO 'login';
GRANT ALL ON procedure `mydb`.`checkUser` TO 'login';
GRANT ALL ON procedure `mydb`.`registraRecapito` TO 'login';
GRANT EXECUTE ON procedure `mydb`.`registraUtente` TO 'login';
SET SQL_MODE = '';
DROP USER IF EXISTS utente;
SET SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';
CREATE USER 'utente' IDENTIFIED BY 'utente';

GRANT INSERT, SELECT, UPDATE, TRIGGER ON TABLE `mydb`.`Annuncio` TO 'utente';
GRANT SELECT ON TABLE `mydb`.`Categoria` TO 'utente';
GRANT INSERT, SELECT ON TABLE `mydb`.`Domanda` TO 'utente';
GRANT INSERT, SELECT ON TABLE `mydb`.`Messaggio` TO 'utente';
GRANT INSERT, SELECT ON TABLE `mydb`.`Segue` TO 'utente';
GRANT UPDATE, SELECT ON TABLE `mydb`.`Utente` TO 'utente';
GRANT UPDATE, INSERT, SELECT ON TABLE `mydb`.`Venduto` TO 'utente';
GRANT EXECUTE ON procedure `mydb`.`bacheca` TO 'utente';
GRANT EXECUTE ON procedure `mydb`.`categorie` TO 'utente';
GRANT EXECUTE ON procedure `mydb`.`domande` TO 'utente';
GRANT EXECUTE ON procedure `mydb`.`inserisciAnnuncio` TO 'utente';
GRANT EXECUTE ON procedure `mydb`.`inviaDomanda` TO 'utente';
GRANT EXECUTE ON procedure `mydb`.`inviaMessaggio` TO 'utente';
GRANT EXECUTE ON procedure `mydb`.`modificaAnnuncio` TO 'utente';
GRANT EXECUTE ON procedure `mydb`.`rimuoviAnnuncio` TO 'utente';
GRANT EXECUTE ON procedure `mydb`.`segnaVenduto` TO 'utente';
GRANT EXECUTE ON procedure `mydb`.`vediAnnunciSeguiti` TO 'utente';
GRANT EXECUTE ON procedure `mydb`.`vediMessRicevuti` TO 'utente';
GRANT EXECUTE ON procedure `mydb`.`vediMessInviati` TO 'utente';
GRANT EXECUTE ON procedure `mydb`.`registraRecapito` TO 'utente';
GRANT INSERT ON TABLE `mydb`.`Contatto` TO 'utente';
GRANT SELECT ON TABLE `mydb`.`annunciSeguiti` TO 'utente';
GRANT EXECUTE ON procedure `mydb`.`modInfoCarta` TO 'utente';
GRANT EXECUTE ON procedure `mydb`.`modInfo` TO 'utente';

SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

-- -----------------------------------------------------
-- Data for table `mydb`.`Categoria`
-- -----------------------------------------------------
START TRANSACTION;
USE `mydb`;
INSERT INTO `mydb`.`Categoria` (`Nome`, `Categoria_Nome`) VALUES ('Motori', NULL);
INSERT INTO `mydb`.`Categoria` (`Nome`, `Categoria_Nome`) VALUES ('Immobili', NULL);
INSERT INTO `mydb`.`Categoria` (`Nome`, `Categoria_Nome`) VALUES ('Lavoro', NULL);
INSERT INTO `mydb`.`Categoria` (`Nome`, `Categoria_Nome`) VALUES ('Elettronica', NULL);
INSERT INTO `mydb`.`Categoria` (`Nome`, `Categoria_Nome`) VALUES ('Casalinghi', NULL);
INSERT INTO `mydb`.`Categoria` (`Nome`, `Categoria_Nome`) VALUES ('Hobby-Sport', NULL);
INSERT INTO `mydb`.`Categoria` (`Nome`, `Categoria_Nome`) VALUES ('Altro', NULL);
INSERT INTO `mydb`.`Categoria` (`Nome`, `Categoria_Nome`) VALUES ('Automobili', 'Motori');

COMMIT;


-- -----------------------------------------------------
-- Data for table `mydb`.`Utente`
-- -----------------------------------------------------
START TRANSACTION;
USE `mydb`;
INSERT INTO `mydb`.`Utente` (`Username`, `Nome`, `Cognome`, `IndirizzoResidenza`, `IndirizzoFatturazione`, `NumeroCC`, `ScadenzaCC`, `Pass_word`) VALUES ('utente1', 'Mario', 'Rossi', 'Via_Roma', NULL, NULL, NULL, 'b88d6b04a9dc38860301f6bdd81e5ccd');
INSERT INTO `mydb`.`Utente` (`Username`, `Nome`, `Cognome`, `IndirizzoResidenza`, `IndirizzoFatturazione`, `NumeroCC`, `ScadenzaCC`, `Pass_word`) VALUES ('utente2', 'Antonio', 'Bianchi', 'Via_Nazionale', 'Via_Italia', NULL, NULL, 'f7a88d7c3168218b580aa68ab3030491');
INSERT INTO `mydb`.`Utente` (`Username`, `Nome`, `Cognome`, `IndirizzoResidenza`, `IndirizzoFatturazione`, `NumeroCC`, `ScadenzaCC`, `Pass_word`) VALUES ('utente3', 'Carlo', 'Medici', 'Via_Europa', NULL, 123456, '0990', 'd3dc39b29f873ec94631cdbe4e92dbf7');
INSERT INTO `mydb`.`Utente` (`Username`, `Nome`, `Cognome`, `IndirizzoResidenza`, `IndirizzoFatturazione`, `NumeroCC`, `ScadenzaCC`, `Pass_word`) VALUES ('utente4', 'Maria', 'Callas', 'Via_Mediterraneo', 'ViadelCorso', 54321, '9009', '4ae57130f9a401c10ce0f017c628262d');
INSERT INTO `mydb`.`Utente` (`Username`, `Nome`, `Cognome`, `IndirizzoResidenza`, `IndirizzoFatturazione`, `NumeroCC`, `ScadenzaCC`, `Pass_word`) VALUES ('gestore', 'admin', 'admin', 'admin', NULL, NULL, NULL, 'ae8dd69bef648b58c635d887844d6dec');

COMMIT;


-- -----------------------------------------------------
-- Data for table `mydb`.`Annuncio`
-- -----------------------------------------------------
START TRANSACTION;
USE `mydb`;
INSERT INTO `mydb`.`Annuncio` (`idAnnuncio`, `Descrizione`, `Foto`, `UltimaModifica`, `Stato`, `Categoria_Nome`, `Utente_Username`) VALUES (DEFAULT, 'bmw_320', NULL, '08/02/2020_17.25', 'vendita', 'Motori', 'utente3');
INSERT INTO `mydb`.`Annuncio` (`idAnnuncio`, `Descrizione`, `Foto`, `UltimaModifica`, `Stato`, `Categoria_Nome`, `Utente_Username`) VALUES (DEFAULT, 'pianoforte_yamaha', NULL, '08/02/2020', 'vendita', 'Altro', 'utente3');
INSERT INTO `mydb`.`Annuncio` (`idAnnuncio`, `Descrizione`, `Foto`, `UltimaModifica`, `Stato`, `Categoria_Nome`, `Utente_Username`) VALUES (DEFAULT, 'notebook_acer', NULL, '07/02/2020', 'vendita', 'Elettronica', 'utente3');
INSERT INTO `mydb`.`Annuncio` (`idAnnuncio`, `Descrizione`, `Foto`, `UltimaModifica`, `Stato`, `Categoria_Nome`, `Utente_Username`) VALUES (DEFAULT, 'villa_Fiumicino', NULL, '07/02/2020', 'rimosso', 'Immobili', 'utente4');
INSERT INTO `mydb`.`Annuncio` (`idAnnuncio`, `Descrizione`, `Foto`, `UltimaModifica`, `Stato`, `Categoria_Nome`, `Utente_Username`) VALUES (DEFAULT, 'kawasaki ninja', NULL, '07/02/2020', 'venduto', 'Motori', 'utente4');
INSERT INTO `mydb`.`Annuncio` (`idAnnuncio`, `Descrizione`, `Foto`, `UltimaModifica`, `Stato`, `Categoria_Nome`, `Utente_Username`) VALUES (DEFAULT, 'pc_asus', NULL, '7/02/2020', 'venduto', 'Elettronica', 'utente4');
INSERT INTO `mydb`.`Annuncio` (`idAnnuncio`, `Descrizione`, `Foto`, `UltimaModifica`, `Stato`, `Categoria_Nome`, `Utente_Username`) VALUES (DEFAULT, 'divano_2posti', NULL, '6/2/2020', 'venduto', 'Altro', 'utente3');

COMMIT;


-- -----------------------------------------------------
-- Data for table `mydb`.`Contatto`
-- -----------------------------------------------------
START TRANSACTION;
USE `mydb`;
INSERT INTO `mydb`.`Contatto` (`Recapito`, `Utente_Username`, `Tipo`, `Preferito`) VALUES ('10', 'utente1', 'Altro', 1);
INSERT INTO `mydb`.`Contatto` (`Recapito`, `Utente_Username`, `Tipo`, `Preferito`) VALUES ('20', 'utente2', 'Altro', 1);
INSERT INTO `mydb`.`Contatto` (`Recapito`, `Utente_Username`, `Tipo`, `Preferito`) VALUES ('30', 'utente3', 'Altro', 1);
INSERT INTO `mydb`.`Contatto` (`Recapito`, `Utente_Username`, `Tipo`, `Preferito`) VALUES ('40', 'utente4', 'Altro', 1);
INSERT INTO `mydb`.`Contatto` (`Recapito`, `Utente_Username`, `Tipo`, `Preferito`) VALUES ('admin', 'gestore', 'Altro', 1);

COMMIT;


-- -----------------------------------------------------
-- Data for table `mydb`.`Segue`
-- -----------------------------------------------------
START TRANSACTION;
USE `mydb`;
INSERT INTO `mydb`.`Segue` (`Annuncio_idAnnuncio`, `Follower`) VALUES (1, 'utente1');
INSERT INTO `mydb`.`Segue` (`Annuncio_idAnnuncio`, `Follower`) VALUES (2, 'utente1');

COMMIT;


-- -----------------------------------------------------
-- Data for table `mydb`.`Venduto`
-- -----------------------------------------------------
START TRANSACTION;
USE `mydb`;
INSERT INTO `mydb`.`Venduto` (`Prezzo`, `Riscossione`, `Annuncio_idAnnuncio`) VALUES (13000, 0, 5);
INSERT INTO `mydb`.`Venduto` (`Prezzo`, `Riscossione`, `Annuncio_idAnnuncio`) VALUES (100, 0, 6);
INSERT INTO `mydb`.`Venduto` (`Prezzo`, `Riscossione`, `Annuncio_idAnnuncio`) VALUES (200, 0, 7);

COMMIT;


-- -----------------------------------------------------
-- Data for table `mydb`.`Domanda`
-- -----------------------------------------------------
START TRANSACTION;
USE `mydb`;
INSERT INTO `mydb`.`Domanda` (`idDomanda`, `Testo`, `Utente_Username`, `Annuncio_idAnnuncio`) VALUES (DEFAULT, 'è a coda o verticale?', 'utente1', 2);
INSERT INTO `mydb`.`Domanda` (`idDomanda`, `Testo`, `Utente_Username`, `Annuncio_idAnnuncio`) VALUES (DEFAULT, 'diesel o benzina?', 'utente2', 1);

COMMIT;

