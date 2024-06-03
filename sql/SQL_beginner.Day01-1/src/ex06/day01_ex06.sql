SELECT action_date, name as person_name
from person as p,
     (SELECT  order_date as action_date, person_id  FROM person_order
      INTERSECT
      SELECT  visit_date as action_date, person_id FROM person_visits
     ) as inter
where inter.person_id = p.id
ORDER BY action_date, name DESC
