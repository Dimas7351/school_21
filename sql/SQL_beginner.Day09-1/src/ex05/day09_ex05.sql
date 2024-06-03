DROP FUNCTION fnc_persons_female;
DROP FUNCTION fnc_persons_male;

create function fnc_persons(IN pgender varchar DEFAULT 'female')
    returns table(id bigint,
                  name varchar,
                  age integer,
                  gender varchar,
                  address varchar
                 ) as $BODY$
select * from person
where gender = pgender
$BODY$ language sql;

select *
from fnc_persons(pgender := 'male');

select *
from fnc_persons();

