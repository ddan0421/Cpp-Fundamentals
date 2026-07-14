# Grocery List Undo Lab — Summary

## What this lab is about

You are building a grocery list that supports **undo** — like **Ctrl+Z** in a text
editor. Every time the user changes the list, the program remembers **how to reverse
that change**. When the user says "undo," the program runs the most recent reversal.

This is the **Command pattern**: every change is paired with a small "command object"
that knows how to undo itself. These command objects are stored on a **stack**
(last in, first out), so undo always reverses the *most recent* change first.

```
User action  ->  list changes  ->  push an undo command onto the stack
User undo    ->  pop the top command  ->  Execute() reverses the change  ->  delete it
```

---

## File structure

| File | Role | Do you edit it? |
|------|------|-----------------|
| `UndoCommand.h` | Abstract base class. Declares `virtual void Execute() = 0`. | No (read-only) |
| `RemoveLastCommand.h` | Undo for "add" — removes the last item. | Yes — Step 3 |
| `SwapCommand.h` | Undo for "swap" — swaps two items back. | Yes — Step 5 |
| `InsertAtCommand.h` | Undo for "remove at index" — re-inserts the item. | Yes — Step 6 |
| `GroceryList.h` | The list + undo stack + all action methods. | Yes — Steps 4, 5, 6 |
| `GroceryListTest.h` | Test harness. Parses command strings and runs them. | No |
| `main.cpp` | Runs test1 / test2 / test3. | Uncomment tests as you go |

> Everything is header-based except `main.cpp`. There is no separate `.cpp` for the classes.

---

## The two core member variables in `GroceryList`

```cpp
std::vector<std::string> listItems;   // the actual grocery list
std::stack<UndoCommand*> undoStack;   // stack of undo commands waiting to run
```

- `listItems` holds the grocery strings.
- `undoStack` holds **pointers** to command objects. (Pointers, so each command can
  modify the *real* `listItems` later — see "Why pointers?" below.)

---

## What you implement, step by step

| Step | What | Where |
|------|------|-------|
| 3 | `RemoveLastCommand::Execute()` | `RemoveLastCommand.h` |
| 4 | `GroceryList::ExecuteUndo()` | `GroceryList.h` |
| 5 | `SwapCommand` class + `GroceryList::SwapWithUndo()` | `SwapCommand.h`, `GroceryList.h` |
| 6 | `InsertAtCommand` class + `GroceryList::RemoveAtWithUndo()` | `InsertAtCommand.h`, `GroceryList.h` |

---

## The two kinds of methods

### 1. "WithUndo" methods — do the action now, then save the undo

Already done for you as the template (`AddWithUndo`):

```cpp
virtual void AddWithUndo(std::string newItemName) {
   listItems.push_back(newItemName);                  // 1. change the list NOW
   undoStack.push(new RemoveLastCommand(&listItems)); // 2. push the undo command
}
```

Every "WithUndo" method follows this exact two-step shape:
1. Change `listItems`.
2. Push the matching undo command onto `undoStack`.

> Do **not** call `Execute()` inside a "WithUndo" method. The action already happened
> directly. `Execute()` is only for undoing later.

### 2. `ExecuteUndo()` — run the most recent undo

```cpp
virtual void ExecuteUndo() {
   UndoCommand* command = undoStack.top();  // 1. look at the top command
   undoStack.pop();                         // 2. remove it from the stack
   command->Execute();                      // 3. run its undo (polymorphism!)
   delete command;                          // 4. free the memory (graded!)
}
```

You write this **once** and it works for every command type. You never write
"if it's a swap do X, else if it's a remove do Y." Each command knows how to undo
itself via `Execute()`.

---

## How each action maps to its undo

| User action | List change (forward) | Command pushed | Command's `Execute()` (undo) | Must save which data? |
|-------------|-----------------------|----------------|------------------------------|------------------------|
| Add item | `push_back(item)` | `RemoveLastCommand` | `pop_back()` | vector pointer |
| Swap i, j | swap the two slots | `SwapCommand` | swap i and j again | vector pointer, i, j |
| Remove at i | `erase` at index i | `InsertAtCommand` | `insert` item back at i | vector pointer, i, **the removed item** |

> Key idea: a command stores the **inverse operation**, not a full copy of the list.

---

## Each command class has the same shape

Every command:
1. **Inherits** from `UndoCommand`.
2. **Stores** what it needs to reverse one specific action.
3. **Takes** that info in its constructor.
4. **Implements** `Execute()` to perform the reverse.

```cpp
class SomeCommand : public UndoCommand {
private:
   // member variables needed to undo one action
public:
   SomeCommand(/* ...info... */) { /* save it */ }
   void Execute() override { /* reverse the action */ }
};
```

---

## Worked examples

### Example A — Add and undo (Steps 3 & 4)

```
Start: []

add "carrots"
   listItems: [carrots]
   undoStack: [RemoveLastCommand]

add "potatoes"
   listItems: [carrots, potatoes]
   undoStack: [RemoveLastCommand, RemoveLastCommand]

undo
   pop RemoveLastCommand -> Execute() -> pop_back() -> delete
   listItems: [carrots]
   undoStack: [RemoveLastCommand]

undo
   pop RemoveLastCommand -> Execute() -> pop_back() -> delete
   listItems: []
   undoStack: []
```

| Step | listItems | undoStack (top is right) |
|------|-----------|--------------------------|
| add carrots | `[carrots]` | `[RemoveLast]` |
| add potatoes | `[carrots, potatoes]` | `[RemoveLast, RemoveLast]` |
| undo | `[carrots]` | `[RemoveLast]` |
| undo | `[]` | `[]` |

### Example B — Swap and undo (Step 5)

```
listItems:  [chips, cookies, waffles, syrup, ice cream, lettuce]
index:         0       1        2        3        4         5

swap 1 4   (cookies <-> ice cream)
   SwapWithUndo(1, 4):
     - swap listItems[1] and listItems[4] NOW
     - push SwapCommand(&listItems, 1, 4)
   listItems: [chips, ice cream, waffles, syrup, cookies, lettuce]

undo
   pop SwapCommand -> Execute() swaps 1 and 4 AGAIN -> delete
   listItems: [chips, cookies, waffles, syrup, ice cream, lettuce]
```

> Swap is its own inverse: swapping the same two indices twice returns the original
> order. That's why `SwapCommand` only needs the two indices, not the old strings.

### Example C — Remove at index and undo (Step 6)

```
listItems:  [orange juice, apple juice]
index:           0             1

removeat 0
   RemoveAtWithUndo(0):
     - push InsertAtCommand (saves index 0 and "orange juice")
     - erase index 0
   listItems: [apple juice]

undo
   pop InsertAtCommand -> Execute() inserts "orange juice" at index 0 -> delete
   listItems: [orange juice, apple juice]
```

Remove from the **middle**:

```
listItems:  [grapefruit, mango, strawberry]
index:           0         1        2

removeat 1   (remove "mango")
   - InsertAtCommand saves index 1 and "mango"
   - erase index 1  ->  strawberry shifts from index 2 to 1
   listItems: [grapefruit, strawberry]

undo
   insert "mango" at index 1
   listItems: [grapefruit, mango, strawberry]
```

---

## `erase` and `insert` are opposites

| Operation | What it does | Shift effect |
|-----------|--------------|--------------|
| `erase(begin() + i)` | removes the element at index i | items after i move **left** |
| `insert(begin() + i, item)` | adds `item` at index i | items at i and after move **right** |

Erase then insert the **same item** at the **same index** = original list:

```
[A, B, C]  --erase 1-->  [A, C]  --insert 1, B-->  [A, B, C]
```

That is exactly the forward/undo pair for Step 6:
- `RemoveAtWithUndo` -> `erase`
- `InsertAtCommand::Execute()` -> `insert`

The same pairing for Step 3 uses end-only operations:
- `AddWithUndo` -> `push_back`
- `RemoveLastCommand::Execute()` -> `pop_back`

---

## The tests

`main.cpp` defines three test scenarios as lists of command strings. The harness
parses strings like:

- `"add carrots"`   -> `AddWithUndo("carrots")`
- `"swap 1 4"`      -> `SwapWithUndo(1, 4)`
- `"removeat 0"`    -> `RemoveAtWithUndo(0)`
- `"undo"`          -> `ExecuteUndo()`
- `"verify a,b,c"`  -> check that the list is exactly `[a, b, c]`
- `"verify"`        -> check that the list is empty

| Test | Covers | Enable when |
|------|--------|-------------|
| Test 1 | add + undo | After Steps 3 & 4 |
| Test 2 | add + swap + undo | After Step 5 |
| Test 3 | add + remove + swap + many chained undos | After Step 6 |

Test 3 is the full integration test: after a messy sequence of mixed operations,
it undoes a long chain and verifies the list matches the expected state at each step.
It catches bugs the simpler tests miss (wrong saved index, wrong undo order, etc.).

> The autograder also checks things `main.cpp` does not, like **proper deletion** of
> executed undo commands. That is why `ExecuteUndo()` must `delete` each command.

---

## Clarifications (from questions raised while building this)

### Does `command->Execute()` always use `RemoveLastCommand`?
No. The stack stores `UndoCommand*` (a base pointer), but each entry is really a
concrete object (`RemoveLastCommand`, `SwapCommand`, or `InsertAtCommand`). Because
`Execute()` is `virtual`, the call runs the version belonging to the **actual object**
on top of the stack. This is **polymorphism**. In Test 1 it always happens to be
`RemoveLastCommand`, but later it can be any of them.

### What is the point of `Execute()` if the action already happened?
`Execute()` is the **undo**, not the original action.
- The forward action runs in the "WithUndo" method (`AddWithUndo`, `SwapWithUndo`,
  `RemoveAtWithUndo`).
- `Execute()` runs **later**, only when the user undoes, called from `ExecuteUndo()`.

For swap, both the forward action and the undo happen to be "swap two items," but they
run at different times and are still separate steps.

### Why use pointers in the stack and constructors?
Each command must modify the **same** `listItems` vector that lives inside
`GroceryList`. Passing `&listItems` (a pointer) lets the command change the real list
when `Execute()` runs later, instead of a copy.

### Why must `ExecuteUndo()` `delete` the command?
Each `new RemoveLastCommand(...)` / `new SwapCommand(...)` / `new InsertAtCommand(...)`
allocates heap memory. After its undo runs, the command is finished and must be freed,
or the program leaks memory. (The `GroceryList` destructor also deletes any commands
still on the stack when the list is destroyed.)

### Why does `erase` / `insert` use `begin() + index` instead of a plain index?
`std::vector::erase` and `std::vector::insert` take an **iterator** (a position in the
container), not an `int`. `begin()` is the position of index 0, so `begin() + index`
is the position of that index. You ARE using the index — you're just converting it
into the iterator type those functions require. (Indexing with `[i]` reads/writes one
element; `begin() + i` expresses a *position* for insert/erase.) This iterator-based
interface is shared across STL containers, which is why it's the standard idiom.

### Why not use swap + `pop_back()` to remove at an index?
That technique (swap the target with the last element, then `pop_back`) is O(1) but
**reorders** the list, and this lab's tests check exact order. It also makes undo
messy (you'd need to remember which element got swapped in). Stick with
`erase` + `InsertAtCommand`, which preserves order and undoes with a single command.

### Order matters in `RemoveAtWithUndo()`
If your `InsertAtCommand` constructor reads the item from the vector
(`removedItem = (*vector)[index];`), you must push the command **before** erasing,
while the item is still there:

```cpp
undoStack.push(new InsertAtCommand(&listItems, removalIndex)); // reads item first
listItems.erase(listItems.begin() + removalIndex);            // then remove
```

Alternatively, pass the saved string explicitly and erase first:

```cpp
std::string removedItem = listItems[removalIndex];            // save first
listItems.erase(listItems.begin() + removalIndex);
undoStack.push(new InsertAtCommand(&listItems, removalIndex, removedItem));
```

Either works — just keep the constructor and `RemoveAtWithUndo()` consistent.

---

## Quick mental checklist for any new command

1. **What is the forward action?**  -> goes in the "WithUndo" method.
2. **What is the reverse action?**  -> goes in the command's `Execute()`.
3. **What must I save to reverse it later?** -> the command's member variables.
4. **Does `ExecuteUndo()` need changes?** -> No. Pop, `Execute()`, delete handles all.
