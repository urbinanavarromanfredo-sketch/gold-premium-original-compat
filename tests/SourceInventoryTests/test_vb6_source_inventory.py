import hashlib
import json
import tempfile
import unittest
from pathlib import Path

from vb6_source_inventory import scan


class SourceInventoryTests(unittest.TestCase):
    def test_inventory_and_references_are_read_only(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary) / "source"
            root.mkdir()
            form = root / "frmPlayer.frm"
            form.write_text('Private Sub Player_EndOfStream(ByVal Result As Long)\n', encoding="utf-8")
            media = root / "Gold.exe"
            media.write_bytes(b"not executed or modified")
            before = {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in (form, media)}

            report = scan(root)

            paths = {item["path"] for item in report["inventory"]}
            self.assertEqual(paths, {"frmPlayer.frm", "Gold.exe"})
            self.assertIn("EndOfStream", report["references"][0]["terms"])
            self.assertEqual(report["missing_named_forms"],
                             ["frmAuto_A.frm", "frmAuto_B.frm", "frmAuto_C.frm", "frmAuto_D.frm"])
            after = {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in (form, media)}
            self.assertEqual(before, after)

    def test_binary_resource_is_inventoried_but_not_text_searched(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / "layout.frx").write_bytes(b"PlayStateChange\x00")
            report = scan(root)
            self.assertEqual(len(report["inventory"]), 1)
            self.assertEqual(report["references"], [])

    def test_rejects_non_directory(self):
        with tempfile.TemporaryDirectory() as temporary:
            file_path = Path(temporary) / "file.txt"
            file_path.write_text("x", encoding="utf-8")
            with self.assertRaises(ValueError):
                scan(file_path)


if __name__ == "__main__":
    unittest.main()
