select name, count(*) as count_of_visits
from person_visits as vis
         join person as p on vis.person_id = p.id
group by p.name
having count(*)>3
