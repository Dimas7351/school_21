create index idx_person_name on person(upper(name));

set enable_seqscan = true;
explain analyze
select * from person
where upper(name) = 'DMITRIY';

set enable_seqscan = false;
explain analyze
select * from person
where upper(name) = 'DMITRIY';