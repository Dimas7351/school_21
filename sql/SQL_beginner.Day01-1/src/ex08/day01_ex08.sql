select order_date, concat(name, ' (age:', age,')')
as person_information
from person_order
natural join (select id as person_id, name, age from person) as temp
order by order_date, person_information