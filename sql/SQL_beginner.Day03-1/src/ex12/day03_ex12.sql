insert into person_order(id, person_id, menu_id, order_date)
select
    generate_series(
                (select max(id) from person_order)+1,
                (select max(id) from person) + (select max(id) from person_order),
                1
    ),
    generate_series(
            (select min(id) from person),
            (select max(id) from person),
            1
    ),
    (select id from menu where pizza_name='greek pizza'),
    '2022-02-25';