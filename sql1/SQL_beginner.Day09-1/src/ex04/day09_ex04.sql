create function fnc_persons_female()
    returns table(id bigint,
                  name varchar,
                  age integer,
                  gender varchar,
                  address varchar
                 ) as $BODY$
select * from person
where gender = 'female'
$BODY$ language sql;

create function fnc_persons_male()
    returns table(id bigint,
                  name varchar,
                  age integer,
                  gender varchar,
                  address varchar
                 ) as $BODY$
select * from person
where gender = 'male'
$BODY$ language sql;

SELECT *
FROM fnc_persons_male();

SELECT *
FROM fnc_persons_female();


