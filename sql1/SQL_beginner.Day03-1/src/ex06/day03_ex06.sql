select m1.pizza_name, piz1.name as pizzeria_name1,
       piz2.name as pizzeria_name2, m1.price from menu m1
join menu as m2 on m1.price=m2.price
join pizzeria as piz1 on m1.pizzeria_id = piz1.id
join pizzeria as piz2 on m2.pizzeria_id = piz2.id
where m1.pizza_name=m2.pizza_name and m1.id>m2.id
order by pizza_name


