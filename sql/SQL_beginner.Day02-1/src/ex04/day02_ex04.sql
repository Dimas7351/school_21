select pizza_name, p.name as pizzeria_name, price from menu m
join pizzeria p on m.pizzeria_id=p.id
where pizza_name in ('mushroom pizza', 'pepperoni pizza')
order by pizza_name, pizzeria_name