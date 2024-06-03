select p.name from person_order ord
join menu m on m.id=ord.menu_id
join person p on p.id=ord.person_id
where m.pizza_name in ('mushroom pizza', 'pepperoni pizza')
  and p.gender='male' and p.address in ('Moscow','Samara')
order by name desc