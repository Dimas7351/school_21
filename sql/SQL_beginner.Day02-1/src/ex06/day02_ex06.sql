select pizza_name, piz.name as pizzeria_name from person_order as ord
  join menu m on ord.menu_id=m.id
  join pizzeria piz on m.pizzeria_id=piz.id
  join person p on ord.person_id=p.id
where p.name in ('Anna', 'Denis')
order by pizza_name, pizzeria_name
