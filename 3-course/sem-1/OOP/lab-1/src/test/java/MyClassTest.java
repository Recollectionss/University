import gift.model.Gift;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class MyClassTest {

    @Test
    public void testSomeFunctionality() {
        Gift myClass = new Gift("Test");
        String result = myClass.getName();
        assertEquals("Test", result, "Functionality should return Test");
    }
}
