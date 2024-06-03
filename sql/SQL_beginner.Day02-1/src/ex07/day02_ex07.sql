select piz.name as pizzeria_name from person_visits as vis
      join menu m on m.pizzeria_id=vis.pizzeria_id
      join pizzeria piz on piz.id=vis.pizzeria_id
      join person p on p.id=vis.person_id
where visit_date='2022-01-08' and price<800 and p.name='Dmitriy'