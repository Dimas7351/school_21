create unique index idx_person_discounts_unique
    on person_discounts (person_id, pizzeria_id);

SET enable_seqscan TO OFF;
EXPLAIN ANALYZE
SELECT * FROM person_discounts
WHERE person_id = 7 AND pizzeria_id = 2;
