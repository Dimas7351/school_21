SELECT COALESCE(p.name, '-') as person_name, vis.visit_date, COALESCE(piz.name, '-') as pizzeria_name
FROM (SELECT * FROM person_visits WHERE visit_date BETWEEN '2022-01-01' AND '2022-01-03') as vis
         FULL JOIN person as p
                   ON vis.person_id=p.id
         FULL JOIN pizzeria as piz
                   ON piz.id=vis.pizzeria_id
order by person_name, visit_date, pizzeria_name