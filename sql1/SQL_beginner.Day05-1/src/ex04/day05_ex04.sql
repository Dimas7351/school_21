create unique index idx_menu_unique on menu(pizzeria_id, pizza_name);

set enable_seqscan to on;
explain analyze
select pizzeria_id, pizza_name
from menu
where pizza_name = 'cheese pizza' and pizzeria_id = 3;

set enable_seqscan to off;
explain analyze
select pizzeria_id, pizza_name
from menu
where pizza_name = 'cheese pizza' and pizzeria_id = 3;
