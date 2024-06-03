select piz.name as pizzeria_name from person_visits as vis
join person as p on vis.person_id = p.id
join pizzeria as piz on vis.pizzeria_id = piz.id
where p.name='Andrey'
except
select piz.name as pizzeria_name from person_order as ord
join person as p on ord.person_id = p.id
join menu as m on ord.menu_id = m.id
join pizzeria as piz on m.pizzeria_id = piz.id
where p.name='Andrey'
order by pizzeria_name