with cte_pizza as (
    select name, pizza_name from person_order as ord
 join person p on p.id=ord.person_id
 join menu m on ord.menu_id=m.id
    where gender='female'
)

select pep.name from(
(select * from cte_pizza where pizza_name='cheese pizza') as cheese
    join (select * from cte_pizza where pizza_name='pepperoni pizza') as pep
on pep.name=cheese.name)
order by name


