package comparator;

import candy.Candy;
import candy.Root;

import java.util.Comparator;

public class CandyComparator implements Comparator<Candy> {
    @Override
    public int compare(Candy c1, Candy c2) {
        return c1.getType().compareTo(c2.getType());
    }
}