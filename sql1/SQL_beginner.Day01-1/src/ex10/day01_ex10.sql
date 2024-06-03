select p.name as person_name, pizza_name, piz.name as pizzeria_name
from person_order as ord
         join menu as m on ord.menu_id = m.id
         join person as p on ord.person_id = p.id
         join pizzeria as piz on piz.id=m.pizzeria_id
order by person_name, pizza_name, pizzeria_name