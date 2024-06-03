CREATE TABLE person_audit (
                              created timestamp with time zone DEFAULT current_timestamp NOT NULL,
                              type_event CHAR(1) DEFAULT 'I' NOT NULL,
                              row_id bigint NOT NULL,
                              name varchar,
                              age integer,
                              gender varchar,
                              address varchar,
                              constraint ch_type_event CHECK (type_event IN ('I', 'U', 'D'))
);

create or replace function fnc_trg_person_insert_audit() returns trigger as
$BODY$
begin
    insert into person_audit(type_event, row_id, name, age, gender, address)
    values ('I', new.id, new.name, new.age, new.gender, new.address);
    return null;
end
$BODY$
    language plpgsql;

create trigger trg_person_insert_audit
    after insert on person for each row
execute function fnc_trg_person_insert_audit();

INSERT INTO person(id, name, age, gender, address) VALUES (10,'Damir', 22, 'male', 'Irkutsk');
