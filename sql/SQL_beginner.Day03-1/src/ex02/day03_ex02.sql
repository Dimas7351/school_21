select pizza_name, price as menu_id, piz.name as pizzeria_name from menu m
join pizzeria piz on m.pizzeria_id = piz.id
where m.id not in (select menu_id from person_order)
order by pizza_name, price