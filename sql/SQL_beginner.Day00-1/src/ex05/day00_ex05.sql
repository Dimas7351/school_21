select 
  (select name from person as per where per.id = ord.person_id)
from person_order as ord
where (menu_id = 13 or menu_id = 14 or menu_id = 18)
and order_date = '2022-01-07'
order by name

