select p.name, pizza_name, price,
       price*(100-dis.discount)/100 as discount_price,
       piz.name as pizzeria_name
from person_order as ord
         join person as p on ord.person_id=p.id
         join menu as m on ord.menu_id = m.id
         join pizzeria as piz on m.pizzeria_id = piz.id
         join person_discounts as dis on ord.person_id=dis.person_id
    and dis.pizzeria_id=m.pizzeria_id
order by name, pizza_name