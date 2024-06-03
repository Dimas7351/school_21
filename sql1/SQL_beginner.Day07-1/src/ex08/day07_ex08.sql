select address, piz.name, count(*) as count_of_orders
from person_order as ord
         join person as p on ord.person_id = p.id
         join menu as m on ord.menu_id = m.id
         join pizzeria as piz on m.pizzeria_id = piz.id
group by address, piz.name
order by address, piz.name