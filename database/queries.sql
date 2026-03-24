-- Reset database
DELETE FROM `users`;
DELETE FROM `menu`;
DELETE FROM `storage`;

-- Fill database
INSERT INTO `users`(`first_name`, `last_name`, `card_id`, `password`)
VALUES
    ('Sidney Enzo', 'Rodrigues da Silva', '19885', SHA2('1234', 256)),
    ('Mohamed', 'Ratul', '19886', SHA2('2345', 256)),
    ('Toshiro', 'Akira', '19887', SHA2('5678', 256)),
    ('Bhimarjun', 'Sapkota', '19888', SHA2('7890', 256))
;

INSERT INTO `menu`(`label`, `description`, `price`)
VALUES
    ('Tosta mista c/ manteiga', 'Pão, queijo, fiambre e manteiga tostado', 40),
    ('Tosta mista', 'Pão, queijo, fiambre tostado', 35),
    ('Tosta c/ quijo', 'Pão e queijo tostado', 30)
;

INSERT INTO `storage`(`label`, `amount`, `measure`)
VALUES
    ('Pão', 5, 'unit'),
    ('Queijo', 400, 'grams'),
    ('Fiambre', 400, 'grams'),
    ('Manteiga', 200, 'grams')
;

-- Check data
SELECT * FROM `menu` LIMIT 5;

SELECT * FROM `users` LIMIT 5;

SELECT * FROM `storage` LIMIT 5;