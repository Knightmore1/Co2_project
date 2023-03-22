-- MySQL Script generated by MySQL Workbench
-- Thu Mar  9 09:46:34 2023
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema Base_Projet
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema Base_Projet
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `Base_Projet` DEFAULT CHARACTER SET utf8 ;
USE `Base_Projet` ;

-- -----------------------------------------------------
-- Table `Base_Projet`.`Salles`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Base_Projet`.`Salles` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `Batiment` VARCHAR(2) NOT NULL,
  `Etage` INT NOT NULL,
  `Numéro de salle` INT NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Base_Projet`.`Mesure`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Base_Projet`.`Mesure` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `Heure` VARCHAR(45) NOT NULL,
  `CO2` INT NOT NULL,
  `Temp` INT NOT NULL,
  `Hum` VARCHAR(45) NOT NULL,
  `Date` DATE NOT NULL,
  `Salles_id` INT NOT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_Mesure_Salles_idx` (`Salles_id` ASC) VISIBLE,
  CONSTRAINT `fk_Mesure_Salles`
    FOREIGN KEY (`Salles_id`)
    REFERENCES `Base_Projet`.`Salles` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
