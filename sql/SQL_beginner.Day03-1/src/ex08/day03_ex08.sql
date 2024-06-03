insert into menu(id, pizzeria_id, pizza_name, price)
values ((select max(id) from menu)+1,
        (select id from pizzeria where name='Dominos'),
        'sicilian pizza', 900)