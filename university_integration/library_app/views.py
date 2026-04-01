from rest_framework import viewsets
from .models import LibraryRecord
from .serializers import LibrarySerializer

class LibraryViewSet(viewsets.ModelViewSet):
    queryset = LibraryRecord.objects.all()
    serializer_class = LibrarySerializer