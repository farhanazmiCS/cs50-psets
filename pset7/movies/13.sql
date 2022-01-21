SELECT DISTINCT name FROM people WHERE id IN
(SELECT person_id FROM stars WHERE movie_id IN
(SELECT movie_id FROM stars WHERE person_id IN
(SELECT id FROM people WHERE name = "Kevin Bacon"
AND (SELECT id FROM people WHERE birth = 1958))))
AND name IS NOT "Kevin Bacon";