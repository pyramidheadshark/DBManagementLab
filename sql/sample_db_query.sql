CREATE TABLE product (
    ID SERIAL PRIMARY KEY,
    Name VARCHAR(30),
    Category VARCHAR(30)
);

INSERT INTO product (Name, Category) VALUES
    ('Помидоры', 'Овощи'),
    ('Яблоко', 'Фрукты'),
    ('Говядина', 'Мясо');