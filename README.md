# Hairpin_checker

This program has been made in order to check if your provided sequence has a hairpin structure based on the [Nussinov-Jacobson algorithm](https://en.wikipedia.org/wiki/Nussinov_algorithm)


## Compilation

To compile the code, run :

```
make
```

## Execution

To execute the program, use the following command:


```
./Hairpin_Checker <sequence_type> <fasta_file>
```

- `<sequence_type>` can be either DNA or RNA
- `<fasta_file>`: The path to your input FASTA file

## Example

A sample FASTA file is available in example.txt.

```
./Hairpin_Checker DNA example.txt
```

Enjoy!
