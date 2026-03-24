-- The money values are registered in cents

DROP TABLE IF EXISTS `users`;
DROP TABLE IF EXISTS `menu`;
DROP TABLE IF EXISTS `storage`;

CREATE TABLE IF NOT EXISTS `users`(
    `id` INT AUTO_INCREMENT,
    `card_id` CHAR(8) NOT NULL UNIQUE,
    `first_name` VARCHAR(32) NOT NULL,
    `last_name` VARCHAR(32) NOT NULL,
    `password` VARCHAR(256) NOT NULL,
    `balance` INT UNSIGNED NOT NULL DEFAULT 0,
    PRIMARY KEY(`id`)
);

CREATE TABLE IF NOT EXISTS `menu`(
    `id` INT AUTO_INCREMENT,
    `label` VARCHAR(32) NOT NULL UNIQUE,
    `description` TEXT DEFAULT 'No description',
    `price` INT UNSIGNED NOT NULL,
    PRIMARY KEY(`id`)
);

CREATE TABLE IF NOT EXISTS `storage`(
    `id` INT AUTO_INCREMENT,
    `label` VARCHAR(32) NOT NULL UNIQUE,
    `amount` INT UNSIGNED NOT NULL,
    `measure` SET('grams', 'litters', 'unit'),
    PRIMARY KEY(`id`)
);