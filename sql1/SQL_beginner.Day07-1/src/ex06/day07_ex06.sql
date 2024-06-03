select name, count(*) as count_of_orders, round(avg(price),2) as average_price,
max(price) as max_price, min(price) as min_price from person_order as ord
join menu as m on ord.menu_id = m.id
join pizzeria as piz on m.pizzeria_id = piz.id
group by name
order by name