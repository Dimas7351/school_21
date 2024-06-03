CREATE VIEW v_price_with_discount AS
(SELECT person.name, menu.pizza_name, menu.price, CAST(price * 0.9 AS integer)
FROM menu
         JOIN person_order ON menu.id = person_order.menu_id
         JOIN person ON person_order.person_id = person.id
ORDER BY name, pizza_name);
