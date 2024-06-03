set enable_seqscan to on;
explain analyze
select pizza_name, piz.name as pizzeria_name from menu as m
join pizzeria as piz on m.pizzeria_id = piz.id;

set enable_seqscan to off;
explain analyze
select pizza_name, piz.name as pizzeria_name from menu as m
join pizzeria as piz on m.pizzeria_id = piz.id;