CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date(
    IN pperson varchar DEFAULT 'Dmitriy',
    IN pprice numeric DEFAULT 500,
    IN pdate date DEFAULT '2022-01-08')
    RETURNS TABLE (
        name varchar
                  ) AS $BODY$
BEGIN
    RETURN QUERY
        (SELECT piz.name FROM person_visits as vis
                                  JOIN person as p on p.id=vis.person_id
                                  JOIN pizzeria as piz on piz.id=vis.pizzeria_id
                                  JOIN menu as m on m.pizzeria_id=piz.id
         WHERE p.name = pperson AND vis.visit_date = pdate AND m.price < pprice);
END;
$BODY$ LANGUAGE plpgsql;

select *
from fnc_person_visits_and_eats_on_date(pprice := 800);

select *
from fnc_person_visits_and_eats_on_date(pperson := 'Anna',pprice := 1300,pdate := '2022-01-01');
