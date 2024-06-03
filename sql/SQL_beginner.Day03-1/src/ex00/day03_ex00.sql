select pizza_name, price, piz.name as pizzeria_name, visit_date from person_visits as vis
 join person as p on p.id=vis.person_id
 join pizzeria as piz on piz.id=vis.pizzeria_id
 join menu as m on m.pizzeria_id=vis.pizzeria_id
where price between 800 and 1000 and p.name='Kate'
order by 1,2,3