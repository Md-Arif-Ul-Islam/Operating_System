db.students.updateOne(
    { name: "Alice" },
    { $set: { age: 21 } }
);
